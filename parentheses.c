/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:58:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/23 17:22:16 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	cmd_between_par(char *command)
{
	int i;
	int len;

	i = 0;
	while (command[i])
	{
		len = 0;
		if (command[i] == '(')
		{
			i++;
			while (command[i] != ')')
			{
				len++;
				i++;
			}
		}
		i++;
	}
	return (len);
}
int	push_and_pop(char *stack, char *command)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i] == ')')
			count++;
		i++;
	}
	if (count == ft_strlen(stack))
		return (0);
	return (-1);
}
int	parenth(char *command)
{
	int i;
	int j;
	char *stack;
	int closed;
	
	i = 0;
	j = 0;
	stack = malloc(ft_strlen(command) * sizeof(char));
	while (command[i])
	{
		if (command[i] == '(')
			stack[j++] = command[i];
		i++;
	}
	stack[j] = '\0';
	closed = push_and_pop(stack, command);
	if (closed != 0)
		return (-1);
	return 0;
}
