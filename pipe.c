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
    int k;
    t_node *current = node;

    while (current) 
    {
        k = 0;
        while (current->command[k]) 
        {
            if (ft_strcmp(current->command[k], "<<") == 0 && current->arr[k].q == 0) 
            {
                k = -1;
                break;
            }
            k++;
        }
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
            if (k != -1 && i != -1) 
            {
                dup2(i, STDIN_FILENO);
                close(i);
            }
			if (k == -1)
				current->command = apply_redirections(current, *envp, data, 0);
            if (current->next) 
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
			if (k != -1)
				current->command = apply_redirections(current, *envp, data, 0);
            if (current->command && check_command(current->command, envp, node, data))
                exe(*envp, current, data);
            free_all_node(node);
            exit(1);
        }
        if (i != -1 && k != -1)
            close(i);
            
        if (current->next) 
        {
            close(pipefd[1]);
            i = pipefd[0];
        }
        if (k == -1)
            waitpid(pid, NULL, 0);
        current = current->next;
    }
    while (wait(NULL) > 0);
    return 0;
}