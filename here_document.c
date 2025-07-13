/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:49:37 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/13 17:28:38 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	here_doc(char **command, t_command *arr)
{
	int i;
	int fd;
	char *delim;
	char *com;
	char *name;

	i = 0;
	delim = NULL;
	com = NULL;
	while (command[i])
	{
		if (ft_strcmp(command[i], "<<") == 0 && arr[i + 1].q == 0)
		{
			fd = open("name", O_CREAT | O_RDWR, 0644); 
			if (fd == -1)
			{
				perror("minishell");
				return ;
			}
			delim = arr[i + 1].command;
			while (1)
			{
				com = readline("> ");
				write(fd,com,ft_strlen(com));
				write(fd,"\n",1);
				if (ft_strcmp(com, delim) == 0)
				{
					close(fd);
					exit (0);
				}
			}
		}
		i++;
	}
	
}