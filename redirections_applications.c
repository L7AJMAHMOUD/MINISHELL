/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/19 16:50:23 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_output_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
		{
			fd = open(command[i + 1], O_CREAT | O_RDWR, 0777);
			command[i] = NULL;
			dup2(fd, 1);
			close(fd);
		}
		i++;
	}
}

void	redirect_input_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "<") == 0)
		{
			fd = open(command[i + 1], O_CREAT | O_RDWR, 0777);
			command[i] = NULL;
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}	
}
void	apply_redirections(char **command)
{
	int i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
			redirect_output_fd(command);
		else if (ft_strcmp(command[i], "<") == 0)
			redirect_input_fd(command); 
		else if (ft_strcmp(command[i], ">>") == 0)
			printf("fd_adder func\n");
		else if (ft_strcmp(command[i], "<<")  == 0)
			printf("here_doc func\n");
		i++;
	}
}
