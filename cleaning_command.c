/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:06:32 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/13 12:12:58 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int 	is_redirect(char *command)
{
	if (ft_strcmp(command, ">") == 0
		|| ft_strcmp(command, "<") == 0
		|| ft_strcmp(command, ">>") == 0
		|| ft_strcmp(command, "<<") == 0)
			return 0;
	return -1;
}
int new_cmd_size(char **command)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (is_redirect(command[i]) == 0 && command[i + 1])
			i+= 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
	
}

char **copy_list(char **command, t_command *arr)
{
	char **new;
	int i;
	int j;
	
	i = 0;
	j = 0;
	new = malloc((new_cmd_size(command) + 1) * sizeof(char *));
	while (command[i])
	{
		if (is_redirect(command[i]) == 0 && command[i + 1] && arr[i].q == 0)
			i+=2;
		else
		{
			new[j] = ft_strdup(command[i]);
			i++;
			j++;
		}
	}
	new[j] = NULL;
	return (new);
}

char **clean_command(char **command, t_command *arr)       
{
	// list(command);
	char **clean = copy_list(command, arr);
	return(clean);
}

// int main()
// {
// 	char *tab[] = { ">" , "1", "ls", "-la", ">", "3", NULL};
// 	char **t = clean_command(tab);
// 	list(t);
// 	// execve("/usr/bin/ls", t, NULL);
// }