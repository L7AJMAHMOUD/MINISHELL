/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:00 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/03 10:48:36 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_is_the_third(char **command)
{
	int fd;

	fd = open(command[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	command[0] = ft_strdup(command[2]);
	command[1] = NULL;
	dup2(fd, 1);
	close(fd);
}
void redirect_output_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	printf(".%s\n",command[0]);
	printf("..%s\n",command[1]);
	printf("...%s\n",command[2]);
	printf("....%s\n",command[3]);
	if (ft_strcmp(command[0], ">") == 0)
	{
		cmd_is_the_third(command);
		return ; 
	}
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
		{
			fd = open(command[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			command[i] = NULL;
			dup2(fd, 1);
			close(fd);
		}
		i++;
	}
}
