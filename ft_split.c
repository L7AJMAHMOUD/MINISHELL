/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/07 10:10:22 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ln(char *s)
{
	int	length;
	char c;
	int k;

	c = 32;
	k = 0;
	length = 0;
	while (s[length] && s[length] != c)
	{
		if (s[length] == '"')
		{
			k += 1;
			while (s[length] != '"' && s[length + 1])
				length++;
		}
		if (s[length] == '\'')
		{
			k += 1;
			while (s[length] != '\'' && s[length + 1])
				length++;
		}
		length++;
	}
	return (length - k);
}

size_t	count_word(char const *str)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '&' && str [i] != '|')
	{
		while (str[i] == ' ' && str[i] && str[i] != '&')
			i++;
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if ((str [i] != '|' && str[i] != '&') && str[i++])
			k++;
		while (str[i] != ' ' && str[i] && str[i] != '&' && str[i] != '|')
			i++;
	}
	return (k);
}


char	**ft_ultra_split(char *s)
{
	int		words;
	int		i;
	int		j;
	int		k;
	int		w_len;
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = count_word(s);
	arr = malloc ((words + 1) * sizeof(char *));
	if (!arr)
	{
		ft_print("Error : allocation in split\n", 0);
		return (NULL);
	}
	while(j < words)
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		w_len = ln(&s[i]);
		arr[j] = malloc(w_len + 1);
		if (!arr[j])
		{
			ft_print("Error : allocation in split\n", 0);
			while (j >= 0)
			free(arr[j--]);
			free(arr);
			return (NULL);
		}
		k = 0;
		while (k < w_len)
		{
			if (s[i] == '"')
			{
				i++;
				while (s[i] != '"')
					arr[j][k++] = s[i++];
				i++;
			}
			else if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
					arr[j][k++] = s[i++];
				i++;
			}
			else
				arr[j][k++] = s[i++];
		}
		arr[j][k] = 0;
		j++;
	}
	arr[j] = NULL;
	return arr;
}
