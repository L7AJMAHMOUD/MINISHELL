/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:45:09 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/12 17:48:02 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void redirect_input_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "<") == 0)
		{
			fd = open(command[i + 1], O_CREAT | O_RDWR , 0644);
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}
}
