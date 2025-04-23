/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:30:54 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/23 11:21:22 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dsq_detector(char *command)
{
	int	i;
	int	count;
	int	c;

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
			if (count == 2)
				c = 0;
		}
		i++;
	}
	return (count % 2);
}

int	search_first(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (i == 0)
		{
			while (command[i] == ' ')
				i++;
			if (command[i] == '|' || command[i] == '&')
				return (-1);
		}
		i++;
	}
	return (0);
}

int	command_analyze(char *command)
{
	if (search_first(command) != 0)
		return (printf("SYNTAX ERROR 0\n"), -1);
	if (dsq_detector(command) != 0)
		return (printf("SYNTAX ERROR 1\n"), -1);
	if (pipe_detector(command) != 0)
		return (printf("SYNTAX ERROR 2\n"), -1);
	if (and(command, 0 , 0) != 0)
		return (printf("SYNTAX ERROR 3\n"), -1);
	if (or(command, 0, 0) != 0)
		return (printf("SYNTAX ERROR 4\n"), -1);
	return (0);
}
