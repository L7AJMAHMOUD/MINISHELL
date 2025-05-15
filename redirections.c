/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:20 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/15 12:07:01 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_parse(char *command)
{
	int i;
	int err;
	
	i = 0;
	err = 0;
	while (command[i])
	{
		if (command[i] == '>' || command[i] == '<')
		{
			i++;
			while(command[i] == 32)
				i++;
			if (is_something(command[i]) == 0)
				err = 0;
			if (command[i] == '\0' || command[i] == '>' || command[i] == '<')
				err = -404;
		}
		i++;
	}
	if (err == -404)
		return (-1);
	return 0;
}









// > : REDIRECT THE OUTPUT TO A FILE ==> 1> STDOUT, 2> STDERR