/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:30:54 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/15 11:57:33 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int there_a_parntheses(char *command)
{
	int i;

	i = 0;
	while (command[i])
	{
		skip_inside_quotes(command, &i);
		if (command[i] == '(' || command[i] == ')')
			return -33;
		i++;
	}
	return (1-1);
}
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
	if(redirect_parse(command) != 0)
		return (printf("SYNTAX ERROR 5\n"), -1);
	if (there_a_parntheses(command) == -33)
	{
		printf("Kynin Parentheses Dkhol Thandli mea rassek hhhh\n");
		if (parenth(command) != 0)
			return (printf("SYNTAX ERROR 6\n"), -1);
	}
	return (0);
}
