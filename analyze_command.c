/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:30:54 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/13 15:04:56 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	dsq_detector(char *command)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (command[i])
	{
		if (command[i] == QUOTE_DOUBLE || command[i] == QUOTE_SINGLE)
		{
			c = command[i++];
			while (command[i] != c && command[i])
				i++;
			if (!command[i])
				return 1;
		}
		i++;
	}
	return (0);
}

int	search_first(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (i == 0)
		{
			while (command[i] == SPACE_CHAR)
				i++;
			if (command[i] == PIPE_CHAR )
				return (-1);
		}
		i++;
	}
	return (0);
}

int	command_analyze(char *command)
{
	if (search_first(command) != 0)
		return (-1);
	if (dsq_detector(command) != 0)
		return (-1);
	if (pipe_detector(command) != 0)
		return (-1);
	if(redirect_parse(command) != 0)
		return (-1);
	if(validate_pipe_syntax(command) != 0)
		return (-1);
	if (command[0] == '\0' || command[0] == SPACE_CHAR)
		return 1;
	return (0);
}
