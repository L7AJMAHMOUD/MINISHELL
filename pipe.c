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

int pip(t_node *node, char ***envp, t_data *data)
{
	int pipefd[2];
	int i = -1;
	pid_t pid;
	t_node *current = node;

	while (current)
	{
		if (current->next)
		{
			if (pipe(pipefd) == -1)
				return (perror("pipe"), 1);
		}
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);

		if (pid == 0)
		{
			if (i != -1)
			{
				dup2(i, STDIN_FILENO);
				close(i);
			}
			if (current->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (check_command(current->command, envp, current, data))
				exe(current->command, *envp, current, current->arr, data);
			free_all_node(node);
			exit(1);
		}

		if (i != -1)
			close(i);
		if (current->next)
		{
			close(pipefd[1]);
			i = pipefd[0];
		}
		current = current->next;
	}
	while (wait(NULL) > 0);
	return 0;
}