/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:00 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/04 19:01:46 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_output_fd(char **command, t_command *arr, t_data *data, int i)
{
	int	fd;

	if (ft_strcmp(command[i], ">") == 0 && arr[i].q == 0)
	{
		if (!command[i + 1] || (command[i + 1] && ft_strcmp(command[i + 1],
					arr[i + 1].command) && count_word(command[i + 1], 32) != 1))
		{
			data->status = 1;
			return (print_err(arr, i), -1);
		}
		fd = open(command[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			data->status = 1;
			write(2, "minishell : ", 13);
			write(2, arr[i + 1].command, ft_strlen(arr[i + 1].command));
			write(2, " : ", 3);
			return (perror(NULL), -1);
		}
		if (dup2(fd, 1) == -1)
			return (close(fd), perror("dup2 failed"), -1);
		if (close(fd) == -1)
			return (perror("close failed"), -1);
	}
	return (0);
}
