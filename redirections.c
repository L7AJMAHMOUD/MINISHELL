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

int	is_redirection(char *command)
{
	return 0;
}
int	redirect_parse(char *command)
{
	int i;
	int is_right;
	int is_left;
	int err;
	
	i = 0;
	while (command[i])
	{
		if (command[i] == REDIRECT_IN || command[i] == REDIRECT_OUT)
		{
			if (command[i] == REDIRECT_OUT)
				is_right = 1;
			if (command[i] == REDIRECT_IN)
				is_left = 1;
			i++;
			if (command[i] == REDIRECT_OUT && is_left == 1 || command[i] == REDIRECT_IN && is_right == 1)
				err = -404;
			i++;
			while (command[i] == SPACE_CHAR)
				i++;
			if (command[i] == REDIRECT_OUT || command[i] == REDIRECT_IN)
				err = -404;
			if (is_something(command[i]) == 0)
				err = 0;
			if (command[i] == '\0')
				err = -404;
		}
		i++;
	}
	if (err == -404)
		return  -1;
	return 0;
}









// > : REDIRECT THE OUTPUT TO A FILE ==> 1> STDOUT, 2> STDERR