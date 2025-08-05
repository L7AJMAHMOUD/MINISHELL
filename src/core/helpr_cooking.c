/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpr_cooking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:25:31 by abkaram           #+#    #+#             */
/*   Updated: 2025/08/04 22:35:21 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	init_command_array(t_command **arr, t_indexes *indx, char *str)
{
	indx->c = 0;
	indx->i = 0;
	indx->j = 0;
	indx->k = 0;
	indx->p = 0;
	*arr = malloc(sizeof(t_command) * (ft_strlen(str) + 1));
	if (!arr)
		return (1);
	ft_memset(*arr, 0, sizeof(t_command) * (ft_strlen(str) + 1));
	(*arr)[indx->k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(*arr)[indx->k].command)
		return (free(arr), arr = NULL, 1);
	return (0);
}

static t_command	*return_null_if_one(t_command *arr, int i)
{
	if (i == 1)
		return (NULL);
	return (arr);
}

static int	init_quote_state(t_indexes *indx, char *str)
{
	indx->j = 0;
	indx->c = str[indx->i++];
	return (0);
}

t_command	*cleaning(char *str, int p, t_command *arr, t_indexes indx)
{
	if (init_command_array(&arr, &indx, str))
		return (NULL);
	while (str[indx.i])
	{
		if (str[indx.i] == QUOTE_SINGLE || str[indx.i] == QUOTE_DOUBLE)
		{
			arr[indx.k].k = 1;
			if (indx.j != 0)
				if (allocate_next_command(arr, str, &(indx.k), indx.j))
					return (NULL);
			init_quote_state(&indx, str);
			if (indx.c == str[indx.i] && !p && is_empty(str, indx.c, indx.i))
			{
				if (handle_empty_quote_command(arr, &indx, str))
					return (NULL);
				continue ;
			}
			indx.c = complete_quoted_command(arr, str, &indx);
			if (indx.c == 1 || indx.c == 2)
				return (return_null_if_one(arr, indx.c));
		}
		else
			arr[indx.k].command[indx.j++] = str[indx.i++];
	}
	arr[indx.k].command[indx.j] = '\0';
	return (arr[++indx.k].command = NULL, arr->nbr = indx.k, arr);
}

int	is_special_char(char c)
{
	return (c == '$' || c == '\'' || c == '\"' || c == ' ' || c == '\t'
		|| c == '<' || c == '>' || c == '!' || c == '?' || c == '='
		|| c == '+' || c == '-' || c == '/' || c == '|' || c == '&'
		|| c == ';' || c == '*' || c == '[' || c == ']' || c == '('
		|| c == ')' || c == '#' || c == '{' || c == '}');
}
