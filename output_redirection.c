/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:00 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/06 18:08:07 by maen-naj         ###   ########.fr       */
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
	if (command[i + 1][0] == '\0' || count_word(command[i + 1], ' ') != 1)
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
		printf("%s\n",command[i]);
		i++;
	}
}
void	cmd_final(char **command, int i)
{
	int fd;
	int ii;
	
	ii = 0;
	while (command[ii])
	{
		if (ft_strcmp(command[ii], ">") == 0)
		{
			if (ambg_check(command, ii) == -1)
				return ;
			fd = open(command[ii + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			command[ii] = NULL;
			// list(coommand);
			dup2(fd, 1);
			close(fd);
		}

		ii++;
	}
}
void redirect_output_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	
	if (ft_strcmp(command[0], ">") == 0)
	{
		cmd_final(command, i);
		return ; 
	}		
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
		{
			if (ambg_check(command, i) == -1)
				return ;
			fd = open(command[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			command[i] = NULL;
			dup2(fd, 1);
			close(fd);
		}
		i++;
	}
}
