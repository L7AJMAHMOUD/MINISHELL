/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:56:47 by abkaram           #+#    #+#             */
/*   Updated: 2025/04/21 14:47:16 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_node    *command_tokenization(char *command)
{
	char	**tokens;
	t_node	*head;
	t_node	*current;
	t_node 	*new;
	int		i;

	i = 0;
	tokens = ft_split(command, ' ');
	head = NULL;
	current = NULL;
	new = NULL;
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		new = create_node(tokens[i]);
		if (!new)
			return (free_split(tokens), NULL);
		if (!head)
		{
			head = new;
			current = head;
		}
		else
		{
			current->next = new;
			current = current->next;
		}
		i++;
	}
	return (free(tokens), head);
}
