/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:31 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/30 10:56:35 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_err(t_command *arr, int i)
{
	write(2, "minishell : ", 13);
	write(2, arr[i + 1].command, ft_strlen(arr[i + 1].command));
	write(2, " : ", 3);
	write(2, "ambiguous redirect\n", 20);
}

int	append_to_fd(char **command, t_command *arr, t_data *data, int i)
{
	int	fd;

	if (ft_strcmp(command[i], ">>") == 0 && arr[i].q == 0)
	{
		if (!command[i + 1]  || (command[i + 1] && ft_strcmp(command[i + 1], arr[i + 1].command) != 0 && count_word(command[i + 1], ' ') != 1))
		{
			data->status = 1;
			return (print_err(arr, i), -1);
		}
		fd = open(command[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			data->status = 1;
			write(2, "minishell : ", 13);
			write(2, arr[i + 1].command, ft_strlen(arr[i + 1].command));
			write(2, " : ", 3);
			perror(NULL);
			return (-1);
		}
		if (dup2(fd, 1) == -1)
			return (perror("dup2 failed"), -1);
		if (close(fd) == -1)
			return (perror("close failed"), -1);
	}
	return (0);
}
