/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:53:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/07 14:38:06 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int   or(char *command, int i, int k)
{
    while  (command[i])
    {
        skip_inside_quotes(command, &i);
        if (command[i++] == PIPE_CHAR)
        {
            k++;
            if (k > 2)
                return -1;
            if (command[i] != PIPE_CHAR)
            {
                k = 0;
                while (command[i] <= 32)
                    if (!command[i++])
                        return -1;
                if (command[i] == PIPE_CHAR || command[i] == '&')
                    return -1;
            }
        }
        else
            k = 0;
        }
    return (0);
}
