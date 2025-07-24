/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:20 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/24 21:50:28 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_parse(char *command)
{
	int		i;
	char	current;

	i = 0;
	while (command[i])
	{
		if (ft_isdigit(command[i]) && (command[i + 1] == '>'
				|| command[i + 1] == '<'))
		{
			i++;
			if (command[i] == command[i + 1])
				i++;
			else
				i++;
			while (command[i] == ' ')
				i++;
			if (ft_isdigit(command[i]) && command[i + 1] == '>')
				return (-1);
			if (command[i] == '\0')
				return (-1);
			if (command[i] == '>' || command[i] == '<')
				return (-1);
		}
		if (command[i] == REDIRECT_IN || command[i] == REDIRECT_OUT)
		{
			current = command[i];
			i++;
			if (command[i] == current)
				i++;
			while (command[i] == SPACE_CHAR)
				i++;
			if (command[i] == '\0')
				return (-1);
			if (command[i] == REDIRECT_IN || command[i] == REDIRECT_OUT)
				return (-1);
			if (!is_something(&command[i]))
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
