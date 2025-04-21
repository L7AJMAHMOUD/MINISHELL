/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:30:54 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/21 16:14:28 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parentheses(char *command)
// {
// 	int i;

// 	i = 0;
// 	while (command[i])
// 	{
		
// 	}
// }
int   or(char *command)
{
    int i;
    int flag;
    int close;

    i = 0;
    close = 0;
    if (command[i] == '|')
        return (-1);
    while  (command[i])
    {
        if (command[i] == '|' && command[i + 1] == '|' && close == 0)
        {
            flag = 0;
            close = 1;
        }
        else if (command[i] == '|' && command[i + 1] != '|' && close == 0)
        {
            flag = -1;
            close = 1;
        }
		else
			close = 0;
        i++;
    }
    return (flag);
}

int   and(char *command)
{
    int i;
    int flag;
    int close;

    i = 0;
    close = 0;
    if (command[i] == '&')
        return (-1);
    while  (command[i])
    {
        if (command[i] == '&' && command[i + 1] == '&' && close == 0)
        {
            flag = 0;
            close = 1;
        }
        else if (command[i] == '&' && command[i + 1] != '&' && close == 0)
        {
            flag = -1;
            close = 1;
        }
		else
			close = 0;
        i++;
    }
    return (flag);
}

int   pipe_detector(char *command)
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
                return (-1);
		}
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
    return (count % 2);
}
int    command_analyze(char *command)
{
    if (dsq_detector(command) != 0)
    {
        printf("SYNTAX ERROR 1\n");
        return -1;
    }
    if (pipe_detector(command) != 0)
    {
        printf("syntax error 2\n");
        return -1;
    }
    if(and(command) != 0)
    {
        printf("SYNTAX ERROR 3\n");
        return -1;
    }
	if(or(command) != 0)
    {
        printf("SYNTAX ERROR 4\n");
        return -1;
    }
    return (0);
}
