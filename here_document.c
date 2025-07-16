/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:49:37 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/16 03:34:04 by maen-naj         ###   ########.fr       */
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

char	*expand_str(char *command, char **envp)
{
	char *str;
	char *tmp;
	char *varname;
	char *val;
	int i;
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
				var_len = strlen_(&(command[j]));
				varname = malloc(var_len + 1);
				if (!varname)
					return NULL;
				strncpy(varname, &(command[j]), var_len);
				varname[var_len] = '\0';
				tmp = get_variable(varname, envp);
				if (tmp)
					val = ft_strdup(tmp);
				else
					val = NULL;
				str = ft_strdup(&(command[j + var_len]));
				command[j - 1] = 0;
				command = ft_strjoin_(command, val);
				var_len = ft_strlen(command);
				command = ft_strjoin_(command, str);
				j = var_len;
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

char *get_delimiter(char **command)
{
	int l7;

	l7 = 0;
	while (command[l7])
	{
		if (command[l7 + 1] == NULL)
			return (command[l7]);
		l7++;
	}
	return (NULL);
}
void	here_doc(char **command, t_command *arr, char **envp)
{
	int i;
	int fd;
	char *delim;
	char *com;
	char *name;
	char *arr_;
	char buff[1000000];

	i = 0;
	delim = get_delimiter(command);
	com = NULL;
	exit(0);
	while (command[i])
	{
		if (ft_strcmp(command[i], "<<") == 0 && arr[i + 1].q == 0)
		{
			fd = open("name", O_CREAT | O_RDWR, 0644); 
			if (fd == -1)
			{
				perror("minishell");
				return ;
			}
			delim = arr[i + 1].command;
			while (1)
			{
				com = readline("> ");
				if (com[0])
				{
					arr_ = expand_str(com, envp);
					write(fd,arr_,ft_strlen(arr_));
				}
				
				write(fd,"\n",1);
				if (ft_strcmp(com, delim) == 0)
				{
					close(fd);
					fd = open("name", O_CREAT | O_RDWR, 0644); 
					read(fd, buff, 1000000);
					printf("%s\n", buff);
					exit (0);
				}
			}
			
		}
		else if (ft_strcmp(command[i], "<<") == 0)
		{
			fd = open("name", O_CREAT | O_RDWR, 0644); 
			if (fd == -1)
			{
				perror("minishell");
				return ;
			}
			delim = arr[i + 1].command;
			while (1)
			{
				com = readline("> ");
				if (com[0])
				{
					write(fd,com,ft_strlen(com));
				}
				
				write(fd,"\n",1);
				if (ft_strcmp(com, delim) == 0)
				{
					close(fd);
					fd = open("name", O_CREAT | O_RDWR, 0644); 
					read(fd, buff, 1000000);
					printf("%s\n", buff);
					exit (0);
				}
			}
			
		}
		i++;
	}
}
