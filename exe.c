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

static int	strlen_until_char(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*strdup_until_char(const char *src, int c, int *i)
{
	char	*h;

	*i = 0;
	if (!src)
		return (0);
	if (!src[*i])
		return (NULL);
	h = malloc(strlen_until_char(src, c) * sizeof(char) + 1);
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

char	*strjoin_with_slash(char *s1, char *s2)
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

int	find_path_index(char **envp)
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

int	check_invalid_path_or_command(char *path)
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

int	check_path_directory_or_missing(char *path)
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

int	check_if_directory(char *path)
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

char	*print_access_error(char *path)
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

char	*print_no_such_file_error(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	return (NULL);
}

char	*print_permission_denied_error(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": Permission denied\n", 20);
	return (NULL);
}

char	*print_command_not_found_error(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": command not found\n", 20);
	return (NULL);
}

char	*check_executable_or_error(char *tmp, char *path)
{
	if (access(tmp, X_OK) == 0)
		return (tmp);
	return (print_permission_denied_error(path));
}

char	*find_executable_in_path(char **envp, t_data *data, char *path, int *j)
{
	int		i;
	int		k;
	char	*tmp;

	i = find_path_index(envp);
	if (i == -1 && !data->path)
		return (print_access_error(path));
	if (i == -1)
		envp[i] = data->path;
	*j = 5;
	while ((size_t)*j < ft_strlen(envp[i]))
	{
		tmp = strdup_until_char(&envp[i][*j], ':', &k);
		if (!tmp)
			return (NULL);
		*j += k;
		tmp = strjoin_with_slash(tmp, path);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
			return (check_executable_or_error(tmp, path));
		free(tmp);
	}
	return (print_command_not_found_error(path));
}

char	*find_path(char *path, char **envp, t_data *data)
{
	int	j;

	if (check_invalid_path_or_command(path))
		return (NULL);
	if (path[1] == '/' && path[0] == '.')
	{
		if (check_path_directory_or_missing(path))
			return (NULL);
		return (ft_strdup(path));
	}
	if (ft_strchr(path, '/'))
	{
		if (check_if_directory(path))
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		return (print_no_such_file_error(path));
	}
	return (find_executable_in_path(envp, data, path, &j));
}

void	exe(char **envp, t_node *node, t_data *data)
{
	char	*path;
	int		i;
	int		status;

	i = fork();
	if (i == -1)
	{
		perror("minishell");
		return ;
	}
	if (i == 0)
	{
		if (data->fd != -1)
		{
			if (dup2(data->fd, 0) == -1)
			{
				perror("dup2");
				exit(1);
			}
		}
		path = find_path(*(node->command), envp, data);
		if (!path)
			exit(1);
		if (execve(path, node->command, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied\n", 20);
		exit(1);
	}
	// else 
	data->pid[data->id++] = i;
	// wait(&status);
	data->status = wait_for_child(i);
	if (status == 256 || status == 1)
		data->status = 127;
	else if (status % 2 == 0 && status != 0)
		data->status = status / 256;
	return ;
}
