/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:50:17 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/03 14:27:07 by maen-naj         ###   ########.fr       */
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
                if (command[i] == '&' || command[i] == '|')
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
