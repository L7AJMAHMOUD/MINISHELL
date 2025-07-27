/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:31 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/24 21:08:02 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_to_fd(char **command, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">>") == 0)
		{
			fd = open(command[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
			{
				data->status = 1;
				write(2, "minishell : ", 14);
				write(2, command[i + 1], ft_strlen(command[i + 1]));
				write(2, " : ", 3);
				perror(NULL);
				return (-1);
			}
			if (dup2(fd, 1) == -1)
				return (perror("dup2 failed"), -1);
			if (close(fd) == -1)
				return (perror("close failed"), -1);
		}
		i++;
	}
	return (0);
}
