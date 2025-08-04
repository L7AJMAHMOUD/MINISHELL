/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_detec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:55:21 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/04 19:01:49 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_detector(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		skip_inside_quotes(command, &i);
		if (command[i] == PIPE_CHAR)
		{
			i++;
			while (command[i] == SPACE_CHAR)
				i++;
			if (command[i] == '\0')
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
