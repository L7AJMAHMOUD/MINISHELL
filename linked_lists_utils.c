/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:28:31 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/21 14:29:06 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(char *data)
{
	t_node	*head;

	head = malloc(sizeof(t_node));
	if (!head)
		return (NULL);
	head->token = data;
	head->next = NULL;
	return (head);
}

void	delete_node(t_node **head)
{
	t_node	*tmp;

	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}
void	print_list(t_node *head)
{
	t_node *p;

	p = head;

	while(p)
	{
		printf("%s -> ", p-> token);
		p = p-> next;
	}
	printf(" NULL\n");
}