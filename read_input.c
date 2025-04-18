/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/18 15:29:38 by maen-naj         ###   ########.fr       */
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
        command = readline("▄︻デ══━一 💥 > ");
        if (!command)
            break ;
        if (command && *command)
            add_history(command);
        command_tokenization(command);
    }
}
