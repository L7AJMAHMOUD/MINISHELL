/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:50:19 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/06 11:39:01 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i++] != 'n')
			return 0;
	}
	return 1;
}

void echo(char **str, int fd)
{
	int i;
	i = 1;
	if (str[i] && ft_check(str[i]))
	{
		i++;
		while(str[i])
		{
			write(fd, str[i], ft_strlen(str[i]));
			i++;
		}
		return ;
	}
	while(str[i])
	{
		write(fd, str[i], ft_strlen(str[i]));
		i++;
	}
	write(fd, "\n", 1);
	
}

void	pwd(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D')
			break ;
		i++;
	}
	if (!envp[i])
        ft_print("pwd not disponible\n", 0);
    printf("%s\n",&envp[i][4]);
}

