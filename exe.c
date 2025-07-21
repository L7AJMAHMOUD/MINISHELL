/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:53:28 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/16 23:27:36 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != (char)c && str[i])
		i++;
	if (str[i] == (char)c)
		return ((char *)str + i);
	return (NULL);
}

static int	ft_strleen(const char *str, int c)
{
	int	i;

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
		return (NULL);
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

char	*ft_strjoiin(char *s1, char *s2)
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
	return (free(s1), s1 = NULL, str);
}

int	ft_locat(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H')
			return (i);
		i++;
	}
	return (-1);
}

int	che_ck(char *path)
{
	if (ft_strchr(path, ':'))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
		return (1);
	}
	if (ft_strcmp("..", path) == 0)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": command not found\n", 20);
		return (1);
	}
	return (0);
}

int	che_ck_(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 18);
		closedir(dir);
		return (1);
	}
	if (access(path, F_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}

int	check__(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 18);
		closedir(dir);
		return (1);
	}
	return (0);
}

char	*check___(char *path)
{
	if (access(path, F_OK) == 0)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied\n", 20);
		return (NULL);
	}
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	return (NULL);
}

char	*check____(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	return (NULL);
}

char	*check_____(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": Permission denied\n", 20);
	return (NULL);
}

char	*check______(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": command not found\n", 20);
	return (NULL);
}

char	*che(char *tmp, char *path)
{
	if (access(tmp, X_OK) == 0)
		return (tmp);
	return (check_____(path));
}

char	*cnt_(char **envp, t_data *data, char *path, int *j)
{
	int		i;
	int		k;
	char	*tmp;

	i = ft_locat(envp);
	if (i == -1 && !data->path)
		return (check___(path));
	if (i == -1)
		envp[i] = data->path;
	*j = 5;
	while ((size_t)*j < ft_strlen(envp[i]))
	{
		tmp = ft_strduup(&envp[i][*j], ':', &k);
		if (!tmp)
			return (NULL);
		*j += k;
		tmp = ft_strjoiin(tmp, path);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
			return (che(tmp, path));
		free(tmp);
	}
	return (check______(path));
}

char	*find_path(char *path, char **envp, t_data *data)
{
	int	j;

	if (che_ck(path))
		return (NULL);
	if (path[1] == '/' && path[0] == '.')
	{
		if (che_ck_(path))
			return (NULL);
		return (ft_strdup(path));
	}
	if (ft_strchr(path, '/'))
	{
		if (check__(path))
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		return (check____(path));
	}
	return (cnt_(envp, data, path, &j));
}

void	exe(char **envp, t_node *node, t_data *data)
{
	char	*path;
	int		i;
	int		status;

	i = fork();
	if (i == 0)
	{
		// if (data->fd != -1)
		// {
			// lseek(data->fd, 0, SEEK_SET);
		// 	dup2(data->fd, 0);
		// }
		path = find_path(*(node->command), envp, data);
		if (!path)
			exit(1);
		execve(path, node->command, envp);
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied\n", 20);
		exit(1);
	}
	else
		wait(&status);
	data->status = status;
	if (status == 256 || status == 1)
		data->status = 127;
	else if (status % 2 == 0 && status != 0)
		data->status = status / 256;
	return ;
}
