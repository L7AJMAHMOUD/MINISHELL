/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:56:47 by abkaram           #+#    #+#             */
/*   Updated: 2025/04/22 22:31:25 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void node_null(t_node *node)
{
	node->command = 0;
	node->pipe = 0;
	node->and = 0;
	node->or = 0;
    node->next = 0;
}

t_node    *command_tokenization(char *command)
{
	int i;
	t_node *node;
	i = 0;
	// if (ft_strstr(command, " | "))
		// {pipex}
	node = malloc(sizeof(t_node));
	node_null(node);
	if (ft_strstr(command, " &&"))
	{
		node->and = 1;
		node->next = command_tokenization(ft_strstr(command, " &&"));
	}
	else if (ft_strstr(command, " ||"))
	{
		node->or = 1;
		node->next = command_tokenization(ft_strstr(command, " ||"));
	}
	node->command = ft_ultra_split(command);
	return node;
}
