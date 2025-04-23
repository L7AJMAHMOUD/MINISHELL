/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:58:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/23 12:05:11 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parenth(char *command)
{
	int i;
	int	c;

	i = 0;
	while (command[i])
	{
		if (command[i] == '(')
		{
			while (command[i] != ')' && command[i])
				i++;
			if (!')')
				return 1;
		}
		i++;
	}
	return 0;
}
