/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/22 23:33:53 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    and_or(char *command)
{
    int i;

    i = 0;
    while  (command[i + 1])
    {
        if ((command[i] == '&' && command[i + 1] == '&') 
        || (command[i] == '|' && command[i + 1] == '|'))
        {
            
        }
        i++;
    }
}

void    read_input(char **envp)
{
    char *command;
	t_node *node;

    while (1)
    {
        command = readline("▄︻デ══━一💥 > ");
        if (!command)
            break ;
        if (command && *command)
            add_history(command);
        if(command_analyze(command) == 0);
			node = command_tokenization(command);
        exe(node->command, envp);
    }
}
