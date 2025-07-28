/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:56:47 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/24 21:36:00 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_node_flags(t_node *node)
{
	node->command = 0;
	node->pipe = 0;
	node->and = 0;
	node->or = 0;
	node->next = 0;
}
int	count_args(char **tab)
{
	int	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char **ft_join_arr(char **first, char **second)
{
	int		len1 = count_args(first);
	int		len2 = count_args(second);
	char	**result = malloc(sizeof(char *) * (len1 + len2 + 1));
	int		i = 0;
	int		j = 0;

	if (!result)
		return (NULL);
	while (i < len1)
	{
		result[i] = strdup(first[i]);
		i++;
	}
	while (j < len2)
	{
		result[i + j] = strdup(second[j]);
		j++;
	}
	free_all_ul_split(second);
	free_all_ul_split(first);
	result[i + j] = NULL;
	return result;
}
char ** split_fini(char **command, t_command *arr)
{
	if (ft_strcmp(command[0], arr[0].command) != 0)
	{
		char **str = ft_split(command[0], ' ');
		command = ft_join_arr(str, command);
		return command;
	}
	return command;
}

void    command_tokenization(t_node **node, char *command, char **envp, t_data *data)
{
	int i;
	t_node *t_mp;
	t_node *t_p;
	t_mp = NULL;

	i = 0;
	if (!command)
		return ;
	if(!*node)
	{
		*node = malloc(sizeof(t_node));
		if (!(*node))
			return ;
		reset_node_flags(*node);
	}
	(*node)->hd = 0;
	if (ft_strstr(command, "|"))
	{
		command_tokenization(&t_mp ,ft_strstr(command, "|"), envp, data);
		if (!(*node)->next)
			(*node)->next = t_mp;
		else
		{
			t_p = (*node)->next;
			(*node)->next = t_mp;
			t_mp->next = t_p;
		}
		i = ft_strt(command, "|");
		command[i] = 0;
		command_tokenization(node ,command, envp, data);
	}
	else
	{
		(*node)->arr = ft_ultr_split(command, envp, 1, data);
		(*node)->i = (*node)->arr->nbr;
		(*node)->command = split_fini(ft_ultra_split(command, envp, data), (*node)->arr);
	}
}

