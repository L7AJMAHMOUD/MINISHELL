/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:56:47 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/19 12:05:04 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void node_null(t_node *node)
{
	node->command = 0;
	node->pipe = 0;
	node->and = 0;
	node->or = 0;
    node->next = 0;
}
char *ft_strdup_p(char *command)
{
	int i;
	char *str;
	
	i = ft_strlen(command);
	while (command[i] != ')')
		i--;
	str = malloc (i + 1);
	if (!str)
	return NULL;
	str[i--] = 0;
	while (i >= 0)
	{
		str[i] = command[i];
		i--;
	}
	return str;
}

int analyse(char *command)
{
	int i;
	int j;
	int k;

	i = 0;
	while(command[i] == '(')
		i++;
	j = i;
	if (i == 0)
	return 0;
	else
	while (command [j] != ')')
	j++;
	k = j;
	while(command[k] == ')')
	k++;
	k = k - j;
	if (i < k)
		return 1;
	return 0;
}

int check(char *command)
{
	int i;
	// i = 0;
	// while (command[i] <= 32)
	// 	i++;
	// if (command[i++] == '(')
	// {
	// 	i++;
	// 	while (command[i] != ')')
	// 		i++;
	// 	if (command[i + 1])
	// 		return 1;
	// }
	i = ft_strlen(command);
	while (command[i] <= 32)
		i--;
	if (command[i] != ')')
		return 1;
	return 0;
}

char	*ft_strstr_pare(char *command)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (check(command))
			return NULL;
		if (command[i] == '(')
		{
			i++;
			if (analyse(&command[i]))
				return ft_strdup(" ");
			command = ft_strdup_p(&command[i]);
			return (command);
		}
		else if (command[i] > 32)
			break;
		i++;
		
	}
	return NULL;
}

void    command_tokenization(t_node **node, char *command)
{
	int i;
	
	char *tmp;
	t_node *t_mp;
	t_node *t_p;
	t_mp = NULL;

	i = 0;
	if (!command)
		return ;
	tmp = ft_strstr_pare(command);
	if (tmp)
		command = tmp;
	if(!*node)
	{
		*node = malloc(sizeof(t_node));
		if (!(*node))
			return ;
		node_null(*node);
	}
	if (ft_strstr(command, "&&"))
	{
		command_tokenization(&t_mp ,ft_strstr(command, "&&"));
		if (!(*node)->next)
			(*node)->next = t_mp;
		else
		{
			t_p = (*node)->next;
			(*node)->next = t_mp;
			t_mp->next = t_p;
		}
		i = ft_strt(command, "&&");
		command[i] = 0;
		command_tokenization(node ,command);
	}
	else if ((*node)->or == 1 && ft_strstr(command, " ||"))
	{
		command_tokenization(&t_mp ,ft_strstr(command, "||"));
		if (!(*node)->next)
			(*node)->next = t_mp;
		else
		{
			t_p = (*node)->next;
			(*node)->next = t_mp;
			t_mp->next = t_p;
		}
		i = ft_strt(command, "||");
		command[i] = 0;
		command_tokenization(node ,command);
	}
	else
		(*node)->command = ft_ultra_split(command);
}

