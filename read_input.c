/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/18 21:49:30 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    command_tokenization(char *command)
{
    char **tokens;

    tokens = ft_split(command, ' ');
    
    int i = 0;

    while(tokens[i])
    {
        printf("%s\n",tokens[i]);
        i++;
    }
}
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
        command_tokenization(command);
    }
}
