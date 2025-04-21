/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:28:37 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/21 15:16:34 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"



void    read_input()
{
    char *command;

    while (1)
    {
        command = readline("▄︻デ══━一💥 > ");
        if (!command)
            break ;
        if (command && *command)
            add_history(command);
        command_analyze(command);
		// tokens = command_tokenization(command);
    }
}
