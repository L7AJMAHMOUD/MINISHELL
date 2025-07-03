/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:00 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/03 15:34:25 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}
void	cmd_is_the_third(char **command)
{
	int fd;
	
	if (command[1][0] == '\0' || count_word(command[1], ' ') != 1)
	{
		printf("ambiguous redirect\n");
		command[0] = NULL;
		return ;
	}
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
	if (ft_strcmp(command[0], ">") == 0)
	{
		cmd_is_the_third(command);
		return ; 
	}
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
		{
			if (command[i + 1][0] == '\0' || count_word(command[i + 1], ' ') != 1)
			{
				printf("ambiguous redirect\n");
				command[0] = NULL;
				return ;
			}
			fd = open(command[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			command[i] = NULL;
			dup2(fd, 1);
			close(fd);
		}
		i++;
	}
}
