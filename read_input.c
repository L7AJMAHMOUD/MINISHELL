/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/30 15:58:21 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
        command_analyze(command);
        node = command_tokenization(command);
        while (node)
        {
            exe(node->command, envp);
            node = node -> next;
        }
    }
}
