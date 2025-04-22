/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:55:21 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/22 15:31:49 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int   pipe_detector(char *command)
{
    int i;

    i = 0;
    while (command[i])
    {
        // or_single_operator(command, &i);
        xor(command, &i);
        if(command[i] == '|')
        {
            while (command[++i] == ' ')
                i++;
            if (command[i] == '\0')
                return (-1);
        }
        i++;
    }
    return (0);
}