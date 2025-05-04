/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/26 10:37:52 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    read_input(char **envp)
{
    char *command;
	t_node *node;
	t_node *tmp;

    while (1)
    {
        node = NULL;
        command = readline("▄︻デ══━一💥 > ");
        if (!command)
        {
            printf("\nexit\n");
            exit (127);
        }
        if (command)
            add_history(command);
        if(command_analyze(command) == 0)
			command_tokenization(&node, command);
        tmp = node;
        while (tmp)
        {
            exe((tmp)->command, envp);
            tmp = (tmp) -> next;
        }
        // free_all(node);
    }
}
