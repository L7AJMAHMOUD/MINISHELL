/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:20 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/15 13:48:46 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *command)
{
	
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
		if (command[i] == '<' || command[i] == '>')
		{
			if (command[i] == '>')
				is_right = 1;
			if (command[i] == '<')
				is_left = 1;
			i++;
			if (command[i] == '>' && is_left == 1 || command[i] == '<' && is_right == 1)
				err = -404;
			else
				i++;
			while (command[i] == ' ')
				i++;
			if (command[i] == '>' || command[i] == '<')
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