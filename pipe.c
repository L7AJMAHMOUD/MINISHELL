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

int pip(t_node *node, char ***envp)
{
	int pipefd[2];
	pid_t pid1, pid2;
	t_node *cmd1 = node;
	t_node *cmd2 = node->next;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("fork1"), 1);
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);

		if (check_command(cmd1->command, envp, cmd1))
			exe(cmd1->command, *envp, cmd1);

		free_all_node(node);
		exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (perror("fork2"), 1);
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);

		if (check_command(cmd2->command, envp, cmd2))
			exe(cmd2->command, *envp, cmd2);

		free_all_node(node);
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}

