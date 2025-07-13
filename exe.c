/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:53:28 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/13 17:41:05 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strleen(const char *str, int c)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_strduup(const char *src, int c, int *i)
{
	char	*h;

	*i = 0;
	if (!src)
		return (0);
	if (!src[*i])
		return NULL;
	h = malloc(ft_strleen(src, c) * sizeof(char) + 1);
	if (!h)
		return (0);
	while (src[*i] && src[*i] != c)
	{
		h[*i] = src[*i];
		*i += 1;
	}
	h[*i] = '\0';
	*i += 1;
	return (h);
}
char	*ft_strjoiin(char*s1, char *s2)
{
	size_t	k;
	size_t	j;
	char	*str;

	j = 0;
	k = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (str == NULL)
		return (0);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	str[j++] = '/';
	while (s2[k])
		str[j++] = s2[k++];
	str[j] = '\0';
	free(s1);
	return (str);
}
 
int	ft_locat(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
			return i;
		i++;
	}
	return (-1);
}

char	*find_path(char *path, char **envp)
{
	char *tmp;
	int i;
	DIR *dir;
	size_t j;
	int k;

	j = 5;
	if ((path[0] == '/' || path[0] =='.') && access(path, F_OK) == 0)
	{
		dir = opendir(path);
		if (dir)
		{
			write (2, "minishell: ", 11);
			write(2, path, ft_strlen(path));
			write (2, " : Is a directory\n", 18);
			closedir(dir);
			return NULL;
		}
		if (access(path ,X_OK) != 0)
		{
			write (2, "minishell: ", 11);
			write(2, path, ft_strlen(path));
			write (2, " : Permission denied\n", 21);
			return NULL;
		}
		return path;
	}
	else if ((path[0] == '/' || path[0] =='.'))
	{
		write (2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write (2, " : No such file or directory\n", 29);
		return path;
	}
	i = ft_locat(envp);
	if (i == -1)
	{
		// free()
		write (2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write (2, " : No such file or directory\n", 29);
		return NULL;
	}
	while (j < ft_strlen(envp[i]))
	{
		tmp = ft_strduup(&envp[i][j], ':', &k);
		j += k;
		tmp = ft_strjoiin(tmp, path);
		if (access(tmp, F_OK) == 0)
			return tmp;
		free(tmp);
	}
	write(2, path, ft_strlen(path));
	write (2, " : command not found\n", 21);
	return NULL;
}
void	exe(char **command, char **envp, t_node *node, t_command *arr, t_data *data)
{
	char *path;
	int i = fork();
	int status;
	if (i == 0)
	{
		// list(command);
		command = apply_redirections(command, arr, envp);
		// list(command);
		path = find_path(*command, envp);
		if (!path)
			exit(1) ;
		exit (execve(path ,command, envp));
	}
	else
		wait(&status);
	return ;
}
