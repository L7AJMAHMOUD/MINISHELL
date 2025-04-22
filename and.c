/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:50:17 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/22 16:01:25 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   and(char *command)
{
    int flag;
    int close;
    int i;

    flag = 0;
    i = 0;
    close = 0;
    while  (command[i])
    {
        xor(command, &i);
        if (command[i++] == '&')
        {
            if (command[i] != '&')
            {
                while (command[i] <= 32)
                    if (!command[i++])
                        return -1;
                if (command[i] == '&')
                    return -1;
            }
        }
    }
    return (flag);
}


void    xor(char *command, int *i)
{
    if (command[*i] == '"')
    {
        *i += 1;
        while(command[*i] != '"')
            *i += 1;
    }
    else if (command[*i] == '\'')
    {
        *i += 1;
        while(command[*i] != '\'')
            *i += 1;
    }
}

void    and_single_operator(char *command, int *i)
{
    *i += 1;
    while (command[*i] != '&' && command[*i])
        *i += 1;
}