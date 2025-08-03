/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:45:09 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/13 13:56:53 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input_fd(char **command, t_command *arr, t_data *data, int i)
{
	int	fd;

	if (!command[i + 1] || (command[i + 1] && ft_strcmp(command[i + 1],
				arr[i + 1].command) && count_word(command[i + 1], 32) != 1))
	{
		data->status = 1;
		return (print_err(arr, i), -1);
	}
	if (ft_strcmp(command[i], "<") == 0 && arr[i].q == 0)
	{
		fd = open(command[i + 1], O_RDONLY, 0644);
		if (fd == -1)
		{
			data->status = 1;
			write(2, "minishell : ", 13);
			write(2, command[i + 1], ft_strlen(command[i + 1]));
			write(2, " : ", 3);
			return (perror(NULL), -1);
		}
		if (dup2(fd, 0) == -1)
			return (perror("dup2 failed"), -1);
		if (close(fd) == -1)
			return (perror("close failed"), -1);
	}
	return (0);
}
