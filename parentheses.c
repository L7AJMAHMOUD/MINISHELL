/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:58:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/25 16:54:52 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	operator_between_par(char *command)
// {
// 	int i;

// 	i = 0;
// 	while (command[i])
// 	{
// 		while (command[i] == ')')
// 		{
// 			i++;
// 			while (command[i] == ' ' || command[i] != '(')
// 			{
// 				if (command[i] == '&' && command[i + 1] == '&')
// 					return (0);
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (-1);
// }
int	cmd_between_par(char *command)
{
	int i;

	i = 0;
	while (command[i])
	{
		while(command[i] == '(')
		{
			i++;
			while (command[i] == ' ')
				i++;
			if (ft_is_spc(command[i]) != 1)
				return -1;
		}
		i++;
	}
	return 0;
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
	if (push_and_pop(stack, command) != 0 || cmd_between_par(command) != 0)
		return (-1);
	return 0;
}
