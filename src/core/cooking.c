/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:04:09 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:22:52 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand(t_command *arr, t_data *data)
{
	int	i;

	i = 0;
	while (i < arr->nbr)
	{
		if (arr[i].q != 39)
			handle_dollar(arr, i, 0, data);
		if (arr[i].command[0] == 0 && arr[i].q == 0)
		{
			free(arr[i].command);
			arr[i].command = NULL;
		}
		i++;
	}
}

char	*ft_arr_to_str(t_command *arr)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (i < arr->nbr)
	{
		str = ft_strjoin_(str, arr[i++].command);
	}
	free(arr);
	return (str);
}

void	inisia(t_indexes *indx)
{
	indx->i = 0;
	indx->j = 0;
	indx->k = 0;
	indx->p = 0;
	indx->c = 0;
	indx->m = 0;
}

t_command	cooking(char *str, int p, int x, t_data *data)
{
	t_command	arr2;
	t_command	*arr;
	t_indexes	indx;

	arr2.k = 0;
	arr2.ex = 0;
	inisia(&indx);
	arr = cleaning(str, p, NULL, indx);
	arr2.q = arr[0].q;
	arr2.k = arr->k;
	arr->data = data;
	arr->envp = *(data->envp);
	if (!x)
		expand(arr, data);
	arr2.ex = arr->ex;
	arr2.command = ft_arr_to_str(arr);
	free(str);
	return (arr2);
}
