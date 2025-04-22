/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/22 23:28:15 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ln(char *s)
{
	int	length;
	char c;

	c = 32;
	length = 0;
	while (s[length] && s[length] != c && s[length] != '&' && s[length] != '|')
	{
		if (s[length++] == '"')
		{
			while (s[length] != '"' && s[length + 1])
				length++;
		}
	}
	return (length);
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
	arr = malloc ((words + 2) * sizeof(char *));
	if (!arr)
	{
		printf("Error : allocation in split\n");
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
			printf("Error : allocation in split\n");
			while (j >= 0)
			free(arr[j--]);
			free(arr);
			return (NULL);
		}
		k = 0;
		while (k <= w_len)
		{
			if (s[i] == '"')
			{
				i++;
				while (s[i] != '"')
					arr[j][k++] = s[i++];
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
