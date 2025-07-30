/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:00 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/13 13:56:14 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirect_output_fd(char **command, t_data *data)
{
	int i;
	int fd;
	int j;
	
 	i = 0;
	 
	 while (command[i])
	 {
		j = 0;
		if (ft_strcmp(command[i], ">") == 0)
		{
			while (j < 100000)
				j++;
			fd = open(command[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				data->status = 1;
				write(2, "minishell : ", 13);
				write(2, command[i + 1], ft_strlen(command[i + 1]));
				write(2, " : ", 3);
				perror(NULL);
				return -1;
			}
			if (dup2(fd, 1) == -1)
				return (close(fd), perror("dup2 failed"), -1);
			if (close(fd) == -1)
				return (perror("close failed"), -1);
		}
		i++;
	}
	return 0;
}
