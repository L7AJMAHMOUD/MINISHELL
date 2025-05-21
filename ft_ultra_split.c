/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultra_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/21 12:36:06 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_quotes(char *s, int *length, int *k)
{
	if (s[*length] == '"')
		{
			k += 2;
			*length += 1;
			while (s[*length] != '"' && s[*length + 1])
				*length += 1;
		}
		if (s[*length] == '\'')
		{
			k += 2;
			*length += 1;
			while (s[*length] != '\'' && s[*length + 1])
				*length += 1;
		}
}

static int	ln(char *s)
{
	int	length;
	char c;
	int k;

	c = 32;
	k = 0;
	length = 0;
	while (s[length] && s[length] != c && s[length] != '>' && s[length] != '<')
	{
		skip_quotes(s, &length, &k);
		length++;
	}
	if ((s[length] == '<' || s[length] == '>') && length == 0)
	{
		length++;
		if (s[length] == '<' || s[length] == '>')
			return 2;
		return 1;
	}
	return (length - k);
}

size_t	count_word(char const *str)
{
	int	i;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '&' && str[i] != '|')
	{
		while (str[i] == ' ' && str[i] && str[i] != '&' && str[i] != '|')
			i++;
		skip_inside_quotes((char *)str, &i);
		if ((str [i] != '|' && str[i] != '&') && str[i++])
			k++;
		while (str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] && str[i] != '&' && str[i] != '|')
			i++;
		if ((str [i] == '<' || str[i] == '>'))
			k++;
	}
	return (k);
}
int check_alloc(char **arr, int j)
{
	if (!arr[j])
	{
		ft_print("Error : allocation in split\n", 0);
		while (j >= 0)
		free(arr[j--]);
		free(arr);
		return 1;
	}
	return 0;
}

void skip_quotes_copy(char *s, char **arr, int *i, int *k, int j)
{
	char c;

	if (s[*i] == '"' || s[*i] == '\'')
	{
		c = s[*i];
		*i += 1;
		while (s[*i] != c)
		{
			arr[j][*k] = s[*i];
			*i += 1;
			*k += 1;
		}
		*i += 1;
	}
	else
	{
		arr[j][*k] = s[*i];
		*i += 1;
		*k += 1;
	}
}

int skip_space(char *s, int *i)
{
	while (s[*i] == ' ')
			*i += 1;
	if (!s[*i])
		return 1;
	return 0;
}

char	**ft_ultra_split(char *s, int	i, int		j)
{
	int		words;
	int		k;
	int		w_len;
	char	**arr;
	
	if (!s)
	return (NULL);
	words = count_word(s);
	printf("%d\n", words);
	arr = malloc ((words + 1) * sizeof(char *));
	if (!arr)
		return (ft_print("Error : allocation in split\n", 0), NULL);
	while(j < words)
	{
		if (skip_space(s, &i))
			break;
		w_len = ln(&s[i]);
		arr[j] = malloc(w_len + 1);
		if (check_alloc(arr, j))
		return (NULL);
		k = 0;
		while (k < w_len)
			skip_quotes_copy(s, arr, &i, &k, j);
		arr[j++][k] = 0;
		}
		return (arr[j] = NULL, arr);
}
