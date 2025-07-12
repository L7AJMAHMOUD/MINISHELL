/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:06:32 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/12 12:50:20 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int 	data_base(char *command)
{
	if (ft_strcmp(command, ">") == 0
		|| ft_strcmp(command, "<") == 0
		|| ft_strcmp(command, ">>") == 0
		|| ft_strcmp(command, "<<") == 0)
			return 0;
	return -1;
}
int count_list(char **command)
{
	int i;

	i = 0;
	while (command[i])
		i++;
	return (i);
	
}

char **copy_list(char **command)
{
	char **new;
	int i;
	
	i = 0;
	new = malloc((count_list(command) + 1) * sizeof(char *));
	while (command[i])
	{
		if (data_base(command[i]) == 0)
			i += 2;
		else
		{
			printf("X : %s\n",command[i]);
			new[i] = ft_strdup(command[i]);
			i++;
		}
	}
	new[i] = NULL;
	return (new);
}

char **clean_command(char **command)
{
	char **clean = copy_list(command);

	return(clean);
}

int main()
{
	char *tab[] = {"ls" ,">", "1", ">", "2", "date", NULL};
	char **t = clean_command(tab);
	int i = 0;
	while (t[i])
	{
		printf("%s\n", t[i]);
		i++;
	}
	
}