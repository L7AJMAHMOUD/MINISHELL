/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:50:19 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/05 08:58:35 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(char **str, int fd)
{
	int i;
	i = 1;
	if (str[i] && ft_strcmp(str[i], "-n") == 0)
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

