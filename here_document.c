/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:49:37 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/30 11:27:28 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_hsig;

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	g;
	char	*str;

	j = 0;
	g = 1;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	g = ft_strlen(s) - start;
	if (g >= len)
		g = len;
	str = malloc(sizeof(char) * (g + 1));
	if (str == NULL)
		return (0);
	while (s[start] && j < len)
		str[j++] = s[start++];
	str[j] = '\0';
	return (str);
}
static int strlen_(char *str)
{
	int i;
	i = 0;
	if (!str)
		return 0;
	while (str[i] && str[i] != '$' && str[i] != QUOTE_SINGLE && str[i] != QUOTE_DOUBLE && str[i] != 32 && str[i] != '<' && str[i] != '>')
	{
		i++;
	}
	return i;
}

char	*expand_str(char *command, char **envp, t_data *data)
{
	char *str;
	char *tmp;
	char *varname;
	char *val;
	int j;
	int var_len;
	int p;
	int m;
	j = 0;
	m = 0;
	while(command[j])
	{
		if(command[j++] == '$')
		{
			p = 0;
			m = j;
			while (command[j] == '$')
			{
				j++;
				p++;
			}
			if (!command[j] && !command)
				continue;
			if (p % 2 || (command[j] >= '0' && command[j] <= '9'))
			{
				if (command[j] >= '0' && command[j] <= '9')
					str = ft_strdup(&(command[j + 1]));
				else
					str = ft_strdup(&(command[j]));
				if (command[j - (p + 1)] == '$')
					command[j - ++p] = 0;
				else
					command[j - p] = 0;
				command = ft_strjoin_(command, str);
				j = m;
			}
			else
			{
				if (command[j] == '?')
				{
					var_len = 1;
					varname = malloc(var_len + 1);
					if (!varname)
						return NULL;
					strncpy(varname, &(command[j]), var_len);
					varname[var_len] = '\0';
					tmp = ft_itoa(data->status);
					if (tmp)
						val = ft_strdup(tmp);
					else
						val = NULL;
					str = ft_strdup(&(command[j + var_len]));
					command[j - 1 - p] = 0;
					command = ft_strjoin_(command, val);
					var_len = ft_strlen(command);
					command = ft_strjoin_(command, str);
					j = var_len;
					free(varname);
					continue;
				}
				var_len = strlen_(&(command[j]));
				varname = malloc(var_len + 1);
				if (!varname)
					return NULL;
				strncpy(varname, &(command[j]), var_len);
				varname[var_len] = '\0';
				tmp = get_variable(varname, envp, data);
				if (tmp)
					val = ft_strdup(tmp);
				else
					val = NULL;
				str = ft_strdup(&(command[j + var_len]));
				command[j - 1 - p] = 0;
				command = ft_strjoin_(command, val);
				var_len = ft_strlen(command);
				command = ft_strjoin_(command, str);
				j = var_len;
				free(varname);
			}
		}
	}
	if (command[0] == 0)
	{
		free(command);
		command = NULL;
	}
	return command;
}

int	delimiters_counter(t_command *arr,char **h)
{
	int i = 0;
	int count  = 0;

	while (h[i])
	{
		if (ft_strcmp(arr[i].command, "<<") == 0 && arr[i + 1].command)
		{
			i += 2;
			count++;
		}
		else
			i++;
	}
	return (count);
}
char **get_delimiters(t_command *arr, char **h)
{
	int delim = delimiters_counter(arr, h);
	char **deli_stack = malloc((delim  + 1) * sizeof(char *));

	int i = 0;
	int j = 0;

	if (!deli_stack)
		return (NULL);
	while (h[i])
	{
		if (ft_strcmp(arr[i].command, "<<") == 0 && arr[i + 1].command)
		{
			deli_stack[j] = ft_strdup(arr[i + 1].command);
			i++;
			j++;
		}
		else
			i++;
	}
	deli_stack[j] = NULL;
	return (deli_stack);
}

long long file_size(int fd)
{
	struct stat st;
    if (fstat(fd, &st) == -1) 
	{
        perror("fstat");
        close(fd);
        return 1;
    }
	return (st.st_size);
}

void heredoc_child_cleanup(char **limiters, char *file, char *com)
{
	if (limiters) free_all_ul_split(limiters);
	if (file) free(file);
	if (com) free(com);
}
int here_doc(t_node* node, char **envp, t_data *data)
{
    int i = 0;
    int j;
    int fd;
    char *com;
    char *arr_;
    int no = 0;
    int nbr_del = 0;
    int status;
	
	g_hsig = 1;
    char *file = here_doc_data();
    char **limiters = get_delimiters(node->arr, node->command);
    if (!limiters || !file)
		return -1;
    
    while (limiters[nbr_del])
	nbr_del++;
	
    pid_t pid = fork();
    
    if (pid == -1)
    {
		perror("fork");
        return -1;
    }
    
    if (pid == 0)
    {
		signal_init_here(data);
		while (node->command[i])
		{
			j = 0;
			if (ft_strcmp(node->command[i], "<<") == 0 && node->arr[i + 1].q == 0)
			{
				fd = open(file, O_CREAT | O_RDWR, 0644); 
				if (fd == -1)
				{
					perror("minishell");
					heredoc_child_cleanup(limiters, file, com);
					exit (-1);
				}
				while (1)
				{
					com = readline("> ");
					if (j != 0 && com)
						write(fd,"\n",1);
					if ((!com || (ft_strcmp(com, limiters[no]) == 0 && limiters[no + 1] == NULL))) 
					{
						if (!com)
							ft_print("minishell: avertissement :« here-document » délimité par la fin du fichier", 0);
						if (!com && limiters[no + 1] != NULL)
						{
							no++;
							continue;
						}
						close(fd);
						fd = open(file, O_CREAT | O_RDWR, 0644); 
						data->i = nbr_del;
						data->fd = fd;
						heredoc_child_cleanup(limiters, file, com);
						exit (0);
					}
					if (com[0] && limiters[no + 1] == NULL)
					{
						arr_ = expand_str(com, envp, data);
						if (arr_)
						write(fd,arr_,ft_strlen(arr_));
					}
					j++;
					if (ft_strcmp(com, limiters[no]) == 0)
						no++;
					free(com);
				}
				
			}
			else if (ft_strcmp(node->command[i], "<<") == 0)
			{
				fd = open(file, O_CREAT | O_RDWR, 0644); 
				if (fd == -1)
				{
					perror("minishell");
					heredoc_child_cleanup(limiters, file, com);
					exit (-1);
				}
				while (1)
				{
					com = readline("> ");
					if (j != 0 && com)
						write(fd,"\n",1);
					if (!com || (ft_strcmp(com, limiters[no]) == 0 && limiters[no + 1] == NULL))
					{
						if (!com)
							ft_print("minishell: avertissement :« here-document » délimité par la fin du fichier", 0);
						if (!com && limiters[no + 1] != NULL)
						{
							no++;
							continue;
						}
						close(fd);
						fd = open(file, O_CREAT | O_RDWR, 0644); 
						data->fd = fd;
						data->i = nbr_del;
						heredoc_child_cleanup(limiters, file, com);
						exit (0);
					}
					if (com[0] && limiters[no + 1] == NULL)
					write(fd,com,ft_strlen(com));
						j++;
					if (ft_strcmp(com, limiters[no]) == 0)
						no++;
				}
				
			}
			i++;
		}
		heredoc_child_cleanup(limiters, file, com);
        exit(0);
    }
    else
    {
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			fd = open(file, O_RDONLY);
			free(file);
			free_all_ul_split(limiters);
			if (fd == -1)
			{
				perror("minishell");
				return -1;
			}
			data->fd = fd;
			data->status = WEXITSTATUS(status);
			data->i = nbr_del;
			return 0;
		}
		free(file);
		free_all_ul_split(limiters);
		data->status = WEXITSTATUS(status);
		return -1;

    }
}



void	list(char **command)
{
	int i = 0;

	while (command[i])
	{
		printf("[%s] ->",command[i]);
		i++;
	}
	if (command[i] == NULL)
		printf("NULL\n");
	
}