/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:00 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/12 17:31:31 by maen-naj         ###   ########.fr       */
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
int	ambg_check(char **command, int i)
{
	if (command[i + 1][0] == '\0' || count_word(command[i + 1], SPACE_CHAR) != 1)
	{
		printf("ambiguous redirect\n");
		command[0] = NULL;
		return -1;
	}
	return 0;
}
void	list(char **command)
{
	int i = 0;
	
	while(command[i])
	{
		printf("[%s] -> ",command[i]);
		i++;
	}
	printf("NULL\n\n\n");
}
void redirect_output_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
		{
			if (ambg_check(command, i) == -1)
				return ;
			fd = open(command[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd, 1);
			close(fd);
		}
		i++;
	}
}
