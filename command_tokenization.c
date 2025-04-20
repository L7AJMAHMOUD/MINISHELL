/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:56:47 by abkaram           #+#    #+#             */
/*   Updated: 2025/04/20 10:12:43 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strleen(const char *str, int c)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}


static char	*ft_strduup(const char *src, int c, int *i)
{
	char	*h;

	*i = 0;
	if (!src)
		return (0);
	if (!src[*i])
		return NULL;
	h = malloc(ft_strleen(src, c) * sizeof(char) + 1);
	if (!h)
		return (0);
	while (src[*i] && src[*i] != c)
	{
		h[*i] = src[*i];
		*i += 1;
	}
	h[*i] = '\0';
	*i += 1;
	return (h);
}

static void node_null(t_node *node)
{
	node->command = 0;
	node->flags = 0;
    node->arg = 0;
	node->pipe = 0;
   	node->flag = 0;
	node->and = 0;
	node->or = 0;
    node->next = 0;
}

t_node    *command_tokenization(char *command)
{
	int i;
	int j;
	t_node *node;
	char *str;
	i = 0;
	// if (ft_strstr(command, " | "))
		// {pipex}
	node = malloc(sizeof(t_node));
	node_null(node);
	if (ft_strstr(command, "&&"))
	{
		node->and = 1;
		node->next = command_tokenization(ft_strstr(command, " &&"));
	}
	else if (ft_strstr(command, "||"))
	{
		node->or = 1;
		node->next = command_tokenization(ft_strstr(command, " ||"));
	}
	if (ft_strstr(command, " -"))
		node->flag = 1;
	while(command[i])
	{
		j = 0;
		while (command[i] == ' ')
			i++;
		if (node->and == 1 && command[i] == '&')
			break;
		if (node->or == 1 && command[i] == '|')
			break;
		if (!node->command)
			node->command = ft_strduup(&command[i], 32, &j);
		i = i + j;
		j = 0;
		if (node->flag == 1)
		{
			while (command[i] == ' ')
					i++;
			if (command[i] == '-')
				node->flags = ft_strjoin(node->flags, ft_strduup(&command[i], ' ', &j));
			i = i + j;
			j = 0;
		}
		while (node->flag == 1 && node->flags)
		{
			while (command[i] == ' ')
				i++;
			if (command[i] != '-')
				break;
			str = ft_strduup(&command[i], ' ', &j);
			if (!str)
				break;
			node->flags = ft_strjoin(node->flags, str);	
			i = i + j;
			j = 0;
		}
		while (command[i] == ' ')
			i++;
		if (node->and == 1 && command[i] == '&')
			break;
		if (node->or == 1 && command[i] == '|')
			break;
		if (!node->arg)
			node->arg = ft_strduup(&command[i], 32, &j);
		i++;
	}
	return node;
}
