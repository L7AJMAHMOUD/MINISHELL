/* ************************************************************************** */
/*																		   	  */
/*														:::	  ::::::::        */
/*   pipe.c											 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+		  */
/*   By: user01 <user01@student.42.fr>			  +#+  +:+	   +#+			  */
/*												+#+#+#+#+#+   +#+		   	  */
/*   Created: 2025/05/05 10:34:41 by abkaram		   #+#	#+#			      */
/*   Updated: 2025/07/03 18:29:25 by user01		   ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

static int	check_here_doc(t_node *current)
{
	int	k;

	k = 0;
	while (current->command[k])
	{
		if (ft_strcmp(current->command[k], "<<") == 0
			&& current->arr[k + 1].q == 0)
			return (-1);
		k++;
	}
	return (0);
}

static int	init_pipe(int *pipefd, t_node *current)
{
	if (current->next)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), 1);
	}
	return (0);
}

static void	child_process(t_node *cur, t_data *data, int *fds)
{
	t_indexes	indx;

	if (fds[0] != -1)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (cur->next)
	{
		close(fds[2]);
		dup2(fds[3], STDOUT_FILENO);
		close(fds[3]);
	}
	indx.i = fds[4];
	indx.j = fds[5];
	indx.p = 0;
	cur->command = apply_redirections(cur,
			(data->envp), data, indx);
	if (cur->command && check_command(cur->command, data->envp, cur, data))
		exe(*(data->envp), cur, data);
	free_all_node(cur);
	exit(data->status);
}

static int	handle_child(t_node *cur, t_data *data, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		child_process(cur, data, fds);
	if (fds[0] != -1)
		close(fds[0]);
	if (cur->next)
	{
		close(fds[3]);
		fds[0] = fds[2];
	}
	data->pid[data->id++] = pid;
	return (pid);
}

int	pip(char ***envp, t_data *data, t_node *cur)
{
	int	fds[6];
	int	pid;
	int	i;
	
	signal(SIGQUIT, si);
	init_fds(fds, &i);
	g_hsig = 1;
	while (cur)
	{
		fds[1] = check_here_doc(cur);
		if (init_pipe(&fds[2], cur))
			return (1);
		data->envp = envp;
		pid = handle_child(cur, data, fds);
		if (i != 1 && (fds[1] == -1 || (!cur->next && fds[1] != -1)
				|| (!cur->next->next && cur->next
					&& !cur->next->command[0] && fds[1] != -1)))
		{
			if (fds[1] != -1)
				i = 1;
			waitpid(pid, &data->status, 0);
		}
		cur = cur->next;
	}
	wait_and_update_status(data);
	return (cleanup_fds(), 0);
}
