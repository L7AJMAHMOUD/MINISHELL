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
int strlen_(char *str)
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

// char	*expand_str(char *command, char **envp, t_data *data)
// {
// 	char *str;
// 	char *tmp;
// 	char *varname;
// 	char *val;
// 	int j;
// 	int var_len;
// 	int p;
// 	int m;
// 	command = ft_strdup(command);
// 	j = 0;
// 	m = 0;
// 	while(command[j])
// 	{
// 		if(command[j++] == '$')
// 		{
// 			p = 0;
// 			m = j;
// 			while (command[j] == '$')
// 			{
// 				j++;
// 				p++;
// 			}
// 			if (!command[j] && !command)
// 				continue;
// 			if (p % 2 || (command[j] >= '0' && command[j] <= '9'))
// 			{
// 				if (command[j] >= '0' && command[j] <= '9')
// 					str = ft_strdup(&(command[j + 1]));
// 				else
// 					str = ft_strdup(&(command[j]));
// 				if (command[j - (p + 1)] == '$')
// 					command[j - ++p] = 0;
// 				else
// 					command[j - p] = 0;
// 				command = ft_strjoin_(command, str);
// 				j = m;
// 			}
// 			else
// 			{
// 				if (command[j] == '?')
// 				{
// 					var_len = 1;
// 					varname = malloc(var_len + 1);
// 					if (!varname)
// 						return NULL;
// 					strncpy(varname, &(command[j]), var_len);
// 					varname[var_len] = '\0';
// 					tmp = ft_itoa(data->status);
// 					if (tmp)
// 						val = ft_strdup(tmp);
// 					else
// 						val = NULL;
// 					str = ft_strdup(&(command[j + var_len]));
// 					command[j - 1 - p] = 0;
// 					command = ft_strjoin_(command, val);
// 					var_len = ft_strlen(command);
// 					command = ft_strjoin_(command, str);
// 					j = var_len;
// 					free(varname);
// 					continue;
// 				}
// 				var_len = strlen_(&(command[j]));
// 				varname = malloc(var_len + 1);
// 				if (!varname)
// 					return NULL;
// 				strncpy(varname, &(command[j]), var_len);
// 				varname[var_len] = '\0';
// 				tmp = get_variable(varname, envp, data);
// 				if (tmp)
// 					val = ft_strdup(tmp);
// 				else
// 					val = NULL;
// 				str = ft_strdup(&(command[j + var_len]));
// 				command[j - 1 - p] = 0;
// 				command = ft_strjoin_(command, val);
// 				var_len = ft_strlen(command);
// 				command = ft_strjoin_(command, str);
// 				j = var_len;
// 				free(varname);
// 			}
// 		}
// 	}
// 	if (command[0] == 0)
// 	{
// 		free(command);
// 		command = NULL;
// 	}
// 	return command;
// }

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
int open_heredoc_fd(const char *file)
{
	int fd = open(file, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return fd;
}

int handle_delimiter(char **limiters, int *no, int fd, t_data *data, char *file)
{
	if (!data->com || (ft_strcmp(data->com, limiters[*no]) == 0 && !limiters[*no + 1]))
	{
		if (!data->com)
			ft_print("minishell: warning: here-document delimited by end-of-file", 0);
		if (!data->com && limiters[*no + 1])
		{
			(*no)++;
			return 0;
		}
		close(fd);
		fd = open_heredoc_fd(file);
		data->fd = fd;
		data->i = *no + 1;
		heredoc_child_cleanup(limiters, file, data->com);
		exit(0);
	}
	return (1);
}


void write_expanded(int fd, char *com, t_data *data)
{
	char *arr_ = expand_str(com, *(data->envp), data);
	if (arr_)
	{
		write(fd, arr_, ft_strlen(arr_));
		free(arr_);
	}
	write(fd, "\n", 1);
}

void process_here_doc(t_data *data, char *file, char **limiters, int expand)
{
	int		fd;
	int		no;
	int		j;
	
	j = 0;
	no = 0;
	data->com = NULL;
	fd = open_heredoc_fd(file);
	while (1)
	{
		data->com = readline("> ");
		if (handle_delimiter(limiters, &no, fd, data, file) == 0)
			continue;
		if (expand && data->com[0] && limiters[no + 1] == NULL)
			write_expanded(fd, data->com, data);
		else if (!expand && data->com[0] && limiters[no + 1] == NULL)
		{
			write(fd, data->com, ft_strlen(data->com));
			write(fd, "\n", 1);
		}
		j++;
		if (data->com && ft_strcmp(data->com, limiters[no]) == 0)
			no++;
		free(data->com);
	}
}


void child_(t_data *data, t_node *node, char *file, char **limiters)
{
	int i;
	
	i = 0;
	data->file = file;
	data->limiters = limiters;
	signal_init_here(data);
	while (node->command[i])
	{
		if (ft_strcmp(node->command[i], "<<") == 0)
			process_here_doc(data, file, limiters, node->arr[i + 1].q == 0);
		i++;
	}
	heredoc_child_cleanup(limiters, file, NULL);
	exit(0);
}

static int handle_heredoc_success(char *file, char **limiters, t_data *data, int status, int nbr_del)
{
	int fd = open(file, O_RDONLY);
	free(file);
	free_all_ul_split(limiters);
	if (fd == -1)
		return (perror("minishell"), -1);
	data->fd = fd;
	data->status = WEXITSTATUS(status);
	data->i = nbr_del;
	return (0);
}

static int handle_heredoc_failure(char *file, char **limiters, t_data *data, int status)
{
	free(file);
	free_all_ul_split(limiters);
	data->status = WEXITSTATUS(status);
	return (-1);
}

static int wait_heredoc_child(pid_t pid, char *file, char **limiters, t_data *data, int nbr_del)
{
	int status;

	g_hsig = 1;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return handle_heredoc_success(file, limiters, data, status, nbr_del);
	return handle_heredoc_failure(file, limiters, data, status);
}

int here_doc(t_node *node, char **envp, t_data *data)
{
	int		nbr_del = 0;
	char	**limiters;
	char	*file;
	pid_t	pid;
	
	limiters = get_delimiters(node->arr, node->command);
	file = here_doc_data();
	if (!limiters || !file)
		return (-1);
	while (limiters[nbr_del])
		nbr_del++;
	*(data->envp) = envp;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		child_(data, node, file, limiters);
	return wait_heredoc_child(pid, file, limiters, data, nbr_del);
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
