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

static int helprs_red_par(int *i, char *command)
{
	*i += 1;
	if (command[*i] == command[*i + 1])
		*i += 1;
	else
		*i += 1;
	while (command[*i] == ' ')
		*i += 1;
	if (ft_isdigit(command[*i]) && command[*i + 1] == '>')
		return (-1);
	if (command[*i] == '\0')
		return (-1);
	if (command[*i] == '>' || command[*i] == '<')
		return (-1);
	return (0);
}
static int helprs_red_pars(int *i, char *command, char current)
{
	*i += 1;
	if (command[*i] == current)
		*i += 1;
	while (command[*i] == SPACE_CHAR)
		*i += 1;
	if (command[*i] == '\0')
		return (-1);
	if (command[*i] == REDIRECT_IN || command[*i] == REDIRECT_OUT)
		return (-1);
	if (!is_something(&command[*i]))
		return (-1);
	return (0);
}

int	redirect_parse(char *command)
{
	int		i;
	char	current;

	i = 0;
	while (command[i])
	{
		skip_inside_quotes(command, &i);
		if (ft_isdigit(command[i]) && (command[i + 1] == '>'
				|| command[i + 1] == '<'))
		{
			if (helprs_red_par(&i, command))
				return (-1);
		}
		if (command[i] == REDIRECT_IN || command[i] == REDIRECT_OUT)
		{
			current = command[i];
			helprs_red_pars(&i, command, current);
		}
		else
			i++;
	}
	return (0);
}
