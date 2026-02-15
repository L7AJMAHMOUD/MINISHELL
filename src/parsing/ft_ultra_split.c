/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultra_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:14:34 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:14:35 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ln(char *s)
{
	int		length;
	char	c;
	char	x;

	c = ' ';
	length = 0;
	while (s[length] && s[length] != c && s[length] != '>'
		&& s[length] != '<')
	{
		if (s[length] == QUOTE_SINGLE || s[length] == QUOTE_DOUBLE)
		{
			x = s[length];
			length++;
			while (s[length] != x && s[length])
			{
				length++;
			}
			length++;
			continue ;
		}
		length++;
	}
	while (s[length] == '>' || s[length] == '<')
		length++;
	return (length);
}

char	**ft_arr_to_tab(t_command *arr, int words, int i, int j)
{
	char	**tab;

	if (!arr || words <= 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (free_arr(arr, --words), NULL);
	while (j < words)
	{
		if (!arr[j].command)
		{
			j++;
			continue ;
		}
		tab[i] = ft_strdup(arr[j].command);
		if (!tab[i++])
			return (i--, free_arr(arr, --words), free_all_ul_split(tab), NULL);
		j++;
	}
	tab[i] = 0;
	free_arr(arr, --words);
	return (tab);
}

int	complit_(t_command *arr, int words, int *j, char *tmp)
{
	int	x;
	int	i;
	int	k;

	i = 0;
	while (*j < words)
	{
		x = 0;
		while (tmp[i] == 32)
			i++;
		arr[*j].command = malloc(sizeof(char) * ln(&tmp[i]) + 1);
		if (!arr[*j].command)
			return (free_arr(arr, *j - 1), 1);
		k = i + ln(&tmp[i]);
		while (i < k)
			arr[*j].command[x++] = tmp[i++];
		arr[*j].command[x] = 0;
		*j += 1;
		i++;
	}
	return (0);
}

t_command	*ft_ultr_split(char *str, char **envp, int q, t_data *data)
{
	t_command	*arr;
	int			j;
	int			words;
	char		*tmp;

	j = 0;
	tmp = ft_strdup(str);
	preparation(&tmp, 0);
	rev_(tmp);
	preparation(&tmp, 0);
	rev_(tmp);
	words = count_words(tmp, ' ', 0, 0);
	arr = malloc(sizeof(t_command) * (words + 1));
	if (!arr)
		return (NULL);
	if (complit_(arr, words, &j, tmp))
		return (NULL);
	j = 0;
	data->envp = &envp;
	while (j < words)
	{
		arr[j] = cooking(arr[j].command, j, q, data);
		j++;
	}
	return (arr[j].command = NULL, free(tmp), arr->nbr = words, arr);
}

char	**ft_ultra_split(char *str, char **envp, t_data *data)
{
	t_command	*arr;
	char		**tab;

	arr = ft_ultr_split(str, envp, 0, data);
	tab = ft_arr_to_tab(arr, arr->nbr, 0, 0);
	return (tab);
}
