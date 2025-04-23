/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:53:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/23 11:16:35 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int   or(char *command, int i, int k)
{
    while  (command[i])
    {
        xor(command, &i);
        if (command[i++] == '|')
        {
            k++;
            if (k > 2)
                return -1;
            if (command[i] != '|')
            {
                k = 0;
                while (command[i] <= 32)
                    if (!command[i++])
                        return -1;
                if (command[i] == '|' || command[i] == '&')
                    return -1;
            }
        }
        else
            k = 0;
        }
    return (0);
}



void    or_single_operator(char *command, int *i)
{
    *i += 1;
    while (command[*i] != '|' && command[*i])
        *i += 1;
}
