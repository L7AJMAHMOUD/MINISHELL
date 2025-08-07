/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:13:42 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:13:43 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_pipe_syntax(char *command)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (command[i])
	{
		skip_inside_quotes(command, &i);
		if (command[i] == PIPE_CHAR)
		{
			i++;
			k++;
			if (k > 2)
				return (-1);
			while (command[i] && command[i] <= 32)
				i++;
			if (!command[i] || command[i] == PIPE_CHAR)
				return (-1);
			continue ;
		}
		k = 0;
		i++;
	}
	return (0);
}
