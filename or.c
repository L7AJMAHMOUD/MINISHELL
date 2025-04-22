/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:53:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/22 17:54:59 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int   or(char *command)
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
        if (command[i++] == '|')
        {
            if (command[i] != '|')
            {
                while (command[i] <= 32)
                    if (!command[i++])
                        return -1;
                if (command[i] == '|')
                    return -1;
            }
        }
    }
    return (flag);
}



void    or_single_operator(char *command, int *i)
{
    *i += 1;
    while (command[*i] != '|' && command[*i])
        *i += 1;
}

// ls &&  ls "       && "

// ls ||  ls "       || "

// ld && ls |  "      &&  "

// ld && ls |  "      &&  "