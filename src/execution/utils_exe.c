#include "../../minishell.h"

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
		exit (127);
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
		exit (-1);
	}
	if (access(path, F_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
		exit (127);
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
		exit (-1);
	}
	return (0);
}
