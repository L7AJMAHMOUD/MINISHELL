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

char *find_path(char *path, char **envp, t_data *data)
{
    char *tmp;
    int i;
    DIR *dir;
    size_t j;
    int k;

    j = 5;
    if ((path[0] == '/' || path[0] == '.') && access(path, F_OK) == 0)
    {
		if (ft_strcmp("..", path) == 0)
		{
			write(2, "minishell: ", 11);
			write(2, path, ft_strlen(path));
			write(2, ": command not found\n", 20);
			return NULL;
		}
        dir = opendir(path);
        if (dir)
        {
            write(2, "minishell: ", 11);
            write(2, path, ft_strlen(path));
            write(2, ": Is a directory\n", 17);
            closedir(dir);
            return NULL;
        }
        if (access(path, X_OK) != 0)
        {
            write(2, "minishell: ", 11);
            write(2, path, ft_strlen(path));
            write(2, ": Permission denied\n", 20);
            return NULL;
        }
        return ft_strdup(path);
    }
    else if ((path[0] == '/' || path[0] == '.'))
    {
        write(2, "minishell: ", 11);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        return NULL;
    }
    
    i = ft_locat(envp);
    if (i == -1 && !data->path)
    {
		if (access(path, F_OK) == 0)
        {
			write(2, "minishell: ", 11);
			write(2, path, ft_strlen(path));
			write(2, ": Permission denied\n", 20);
			return NULL;
        }
        write(2, "minishell: ", 11);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        return NULL;
    }
	if (i == -1)
		envp[i] = data->path;
    while (j < ft_strlen(envp[i]))
    {
        tmp = ft_strduup(&envp[i][j], ':', &k);
        if (!tmp)
        {
			printf("hello\n");
			return NULL;
		}
        j += k;
        tmp = ft_strjoiin(tmp, path);
        if (!tmp)
            return NULL;
        if (access(tmp, F_OK) == 0)
        {
            if (access(tmp, X_OK) == 0)
                return tmp;
            else
            {
                free(tmp);
                write(2, "minishell: ", 11);
                write(2, path, ft_strlen(path));
                write(2, ": Permission denied\n", 20);
                return NULL;
            }
        }
        free(tmp);
    }
    write(2, "minishell: ", 11);
    write(2, path, ft_strlen(path));
    write(2, ": command not found\n", 20);
    return NULL;
}
void	exe(char **envp, t_node *node, t_data *data)
{
	char *path;
	int i = fork();
	int status;

	if (i == 0)
	{
		node->command = apply_redirections(node->command, node->arr, envp, data);
		path = find_path(*(node->command), envp, data);
		if (!path)
			exit(1) ;
		exit (execve(path ,node->command, envp));
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
