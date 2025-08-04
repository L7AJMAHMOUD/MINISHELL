/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:06:32 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/04 19:02:28 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**copy_list(char **command, t_command *arr)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc((new_cmd_size(command, arr) + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (command[i])
	{
		if (is_redirect(command[i]) == 0
			&& arr[i + 1].command && arr[i].q == 0)
		{
			i++;
			if (!command[i])
				break ;
			if (ft_strcmp(command[i], "<<") == 0)
				i--;
			i++;
		}
		else
			new[j++] = ft_strdup(command[i++]);
	}
	return (new[j] = NULL, new);
}

char	**clean_command(char **command, t_command *arr)
{
	char	**clean;

	clean = copy_list(command, arr);
	if (!clean)
		return (NULL);
	free_all_ul_split(command);
	return (clean);
}
