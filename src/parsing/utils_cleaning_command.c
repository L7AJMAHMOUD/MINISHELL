/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:15:07 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:15:08 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirect(char *command)
{
	if (ft_strcmp(command, ">") == 0
		|| ft_strcmp(command, "<") == 0
		|| ft_strcmp(command, ">>") == 0
		|| ft_strcmp(command, "<<") == 0)
		return (0);
	return (-1);
}

int	new_cmd_size(char **command, t_command *arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (is_redirect(command[i]) == 0 && command[i + 1] && arr[i].q == 0)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
