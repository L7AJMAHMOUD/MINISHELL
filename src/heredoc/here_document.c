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

void	child_(t_data *data, t_node *node, char *file, char **limiters)
{
	int	i;

	i = 0;
	data->file = file;
	data->limiters = limiters;
	signal_init_here(data);
	while (node->command[i])
	{
		if (node->arr[i].q == 0 && ft_strcmp(node->command[i], "<<") == 0)
			process_here_doc(data, file, limiters, node->arr[i + 1].q == 0);
		i++;
	}
	heredoc_child_cleanup(limiters, file, NULL);
	exit(0);
}

static int	handle_heredoc_success(char *file, t_data *data, int status,
		int nbr_del)
{
	int	fd;

	fd = open(file, O_RDONLY);
	free(file);
	free_all_ul_split(data->limiters);
	if (fd == -1)
		return (perror("minishell"), -1);
	data->fd = fd;
	data->status = WEXITSTATUS(status);
	data->i = nbr_del;
	return (0);
}

static int	handle_heredoc_failure(char *file, char **limiters, t_data *data,
		int status)
{
	free(file);
	free_all_ul_split(limiters);
	data->status = WEXITSTATUS(status);
	return (-1);
}

static int	wait_heredoc_child(pid_t pid, char *file, t_data *data, int nbr_del)
{
	int	status;

	g_hsig = 1;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (handle_heredoc_success(file, data, status, nbr_del));
	return (handle_heredoc_failure(file, data->limiters, data, status));
}

int	here_doc(t_node *node, char **envp, t_data *data)
{
	int		nbr_del;
	char	**limiters;
	char	*file;
	pid_t	pid;

	nbr_del = 0;
	limiters = get_delimiters(node->arr, node->command);
	data->limiters = limiters;
	file = here_doc_data(0, NULL, NULL, NULL);
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
	return (wait_heredoc_child(pid, file, data, nbr_del));
}
