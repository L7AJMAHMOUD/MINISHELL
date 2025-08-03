/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:04:09 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/27 22:10:17 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_command	cooking(char *str, int p, int x, t_data *data)
{
	t_command	arr2;
	t_command	*arr;
	t_indexes	indx;

	arr = cleaning(str, p, NULL, indx);
	arr2.q = arr[0].q;
	arr->data = data;
	arr->envp = *(data->envp);
	if (!x)
		expand(arr, data);
	arr2.command = ft_arr_to_str(arr);
	free(str);
	return (arr2);
}
