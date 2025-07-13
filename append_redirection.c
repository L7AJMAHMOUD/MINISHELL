/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:31 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/13 12:35:17 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void append_to_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">>") == 0)
		{
			fd = open(command[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("minishell");
				exit(0);
			}
			dup2(fd, 1);
			close(fd);
		}
		i++;
	}
}