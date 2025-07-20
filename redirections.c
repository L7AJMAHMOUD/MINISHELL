/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:20 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/07 14:39:41 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_parse(char *command)
{
	int i = 0;
	char current;

	while (command[i])
	{
		if (command[i] == REDIRECT_IN || command[i] == REDIRECT_OUT)
		{
			current = command[i];
			i++;
			if (command[i] == current)
				i++;
			while (command[i] == SPACE_CHAR)
				i++;
			if (command[i] == REDIRECT_IN || command[i] == REDIRECT_OUT || command[i] == '\0')
				return -1;
			if (!is_something(&command[i]))
				return -1;
		}
		else
			i++;
	}
	return 0;
}










// > : REDIRECT THE OUTPUT TO A FILE ==> 1> STDOUT, 2> STDERR