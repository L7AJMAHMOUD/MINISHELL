/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:53:28 by abkaram           #+#    #+#             */
/*   Updated: 2025/08/04 22:23:44 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*strdup_until_char(const char *src, int c, int *i)
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

static void	child_process(t_node *node, char **envp, t_data *data)
{
	char		*path;
	struct stat	st;

	if (data->fd != -1 && dup2(data->fd, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = find_path(*(node->command), envp, data);
	if (!path)
		exit(1);
	if (execve(path, node->command, envp) == -1)
	{
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			print_is_a_directory_error(path);
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		perror(NULL);
		free(path); // path is allocated by find_path
		exit(126);
	}
	print_permission_denied_error(path);
}

void	exe(char **envp, t_node *node, t_data *data)
{
	int	i;
	int	sig;

	i = fork();
	if (i == -1)
		return (perror("minishell"));
	if (i == 0)
		child_process(node, envp, data);
	data->pid[data->id++] = i;
	data->status = wait_for_child(i, data);
	if (WIFSIGNALED(data->status))
	{
		sig = WTERMSIG(data->status);
		if (sig == SIGQUIT)
			write(2, "Quit\n", 5);
		else if (sig == SIGINT)
			write(2, "\n", 1);
		data->status = 128 + sig;
	}
	else if (WIFEXITED(data->status))
	{
		data->status = WEXITSTATUS(data->status);
	}
}
