/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:50:17 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/07 14:40:09 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   and(char *command, int i, int k)
{
    while  (command[i])
    {
        skip_inside_quotes(command, &i);
        if (command[i++] == '&')
        {
            k++;
            if (k > 2)
                return -1;
            if (command[i] != '&')
            {
                k = 0;
                while (command[i] <= 32)
                    if (!command[i++])
                        return -1;
                if (command[i] == '&' || command[i] == PIPE_CHAR)
                    return -1;
            }
        }
        else
            k = 0;
        }
    return (0);
}


void    skip_inside_quotes(char *command, int *i)
{
    if (command[*i] == QUOTE_DOUBLE)
    {
        *i += 1;
        while(command[*i] != QUOTE_DOUBLE)
            *i += 1;
    }
    else if (command[*i] == QUOTE_SINGLE)
    {
        *i += 1;
        while(command[*i] != QUOTE_SINGLE)
            *i += 1;
    }
}
