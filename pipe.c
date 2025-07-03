/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:34:41 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/03 18:11:29 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pip(t_node *node, char ***envp)
{
	int id;
	int i;
	int j;
	t_node *tmp;
	int pipfd[2];
	pid_t pid;
	char *p = NULL;
	char *path;
	int fd[2];
	i  = pipe(pipfd);
	if (i == -1)
		return (perror("Erreur de fork"), 1);
	i = j = 0;
	pid = fork();
	pid_t pid1 = fork();
	if (pid < 0) {
		perror("Erreur de fork");
		return 1;
	}
	if (pid == 0 && pid1 != 0) {
		close (pipfd[1]);	
		dup2(fd[1] ,STDOUT_FILENO);
		dup2( pipfd[0], STDIN_FILENO);
        tmp = node;
        if(check_command((tmp)->command, envp, node))
        {
            exe((tmp)->command, *envp, node);
        }
        free_all_node(node);
		exit (1);
	}
	else if (pid1 == 0 && pid != 0)
	{
		close (pipfd[0]);
        tmp = node -> next;
        if(check_command((tmp)->command, envp, tmp))
        {
            exe((tmp)->command, *envp, tmp);
        }
        free_all_node(node);
		exit (1);
	}
	else
	{
		close(pipfd[0]);
		close(pipfd[1]);
		waitpid(pid, NULL, 0);
		waitpid(pid1, NULL, 0);
	}
	return 0;
}
