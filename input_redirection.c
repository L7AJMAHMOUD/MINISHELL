/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:45:09 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/03 16:01:23 by maen-naj         ###   ########.fr       */
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

void redirect_input_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	if (ft_strcmp(command[0], "<") == 0)
	{
		cmd_is_the_third(command);
		return ; 
	}
	while (command[i])
	{
		if (ft_strcmp(command[i], "<") == 0)
		{
			if (command[i + 1][0] == '\0' || count_word(command[i + 1], ' ') != 1)
			{
				printf("ambiguous redirect\n");
				command[0] = NULL;
				return ;
			}
			fd = open(command[i + 1], O_CREAT | O_RDWR , 0644);
			command[i] = NULL;
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}
}