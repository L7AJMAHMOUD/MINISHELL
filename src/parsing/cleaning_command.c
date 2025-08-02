/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:06:32 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/24 21:32:49 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(char *command)
{
	if (ft_strcmp(command, ">") == 0
		|| ft_strcmp(command, "<") == 0
		|| ft_strcmp(command, ">>") == 0)
		return (0);
	return (-1);
}

int	new_cmd_size(char **command, t_command *arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (is_redirect(command[i]) == 0 && command[i + 1] && arr[i].q == 0)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
int	new_cmd_size_here(char **command, t_command *arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "<<") == 0 && command[i + 1] && arr[i].q == 0)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

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
		if (is_redirect(command[i]) == 0 && command[i + 1] && arr[i].q == 0)
			i += 2;
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
char	**copy_list_here(char **command, t_command *arr)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc((new_cmd_size_here(command, arr) + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (command[i])
	{
		if (ft_strcmp(command[i], "<<") == 0 && command[i + 1] && arr[i].q == 0)
			i += 2;
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

char	**clean_command(char **command, t_command *arr)
{
	char	**clean;

	clean = copy_list(command, arr);
	if (!clean)
		return (NULL);
	free_all_ul_split(command);
	return (clean);
}
char	**clean_command_here(char **command, t_command *arr)
{
	char	**clean;

	clean = copy_list_here(command, arr);
	if (!clean)
		return (NULL);
	free_all_ul_split(command);
	return (clean);
}
