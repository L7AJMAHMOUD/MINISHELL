/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/19 18:17:27 by user01           ###   ########.fr       */
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
int dsq_detector(char *command)
{
    int i;
    int count;
    int c;

    i = 0;
    count = 0;
    c = 0;
    while (command[i])
    {
        if (command[i] == '"' || command[i] == '\'')
        {
            if (c == 0)
                c = command[i];
            if (c == command[i]) 
                count++;
            if(count == 2)
                c = 0;
        }
        i++;
    }
    return (count);
}
void    pipe_detector(char *command)
{
    int i;

    i = 0;
    while (command[i])
    {
		if (i == 0)
		{
			while (command[i] == ' ')
                i++;
			if(command[i] == '|')
				printf("SYNTAX ERROR \n");
		}
        if(command[i] == '|')
        {
            while (command[++i] == ' ')
                i++;
            if (command[i] == '\0')
                printf("SYNTAX ERROR \n");
        }
        i++;
    }
}

void    command_analyze(char *command)
{
    int sdq;

    sdq = dsq_detector(command);
    if (sdq % 2 != 0)
        printf("SYNTAX ERROR \n");
    pipe_detector(command);
    and_or(command);
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
        command_analyze(command);
    }
}
