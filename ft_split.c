/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/22 14:02:59 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ln(char *s)
{
	int	length;
	char c;

	c = 32;
	length = 0;
	while (s[length] && s[length] != c && s[length] != '&')
	{
		if (s[length++] == '"')
		{
			if (!s[length])
				break;
			while (s[length] != '"' && s[length + 1])
				length++;
		}
		length++;
	}
	return (length);
}

size_t	count_word(char const *str)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '&')
	{
		while (str[i] == ' ' && str[i] && str[i] != '&')
			i++;
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i++])
			k++;
		while (str[i] != ' ' && str[i] && str[i] != '&')
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
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = count_word((char *)s);
	arr = malloc ((words+ 1) * sizeof(char *) );
	if (!arr)
	{
		printf("Error : allocation in split\n");
		exit (1);
	}
	while(s[i] && s[i] != '&' && s[i] != '|')
	{
		k = 0;
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		arr[j] = malloc(ln(&s[i]) + 1);
		if (!arr[j])
		{
			printf("Error : allocation in split\n");
			while (j >= 0)
				free(arr[j--]);
			free(arr);
			exit (1);
		}
		while (s[i] && s[i] != ' ' && s[i] != '&' && s[i] != '|')
		{
			if (s[i] == '"')
			{
				i++;
				while (s[i] != '"' && s[i + 1])
				{
					arr[j][k] = s[i];
					k++;
					i++;
				}
				i++;
			}
			else
			{
				arr[j][k] = s[i];
				i++;
				k++;
			}
				
		}
		arr[j][k] = 0;
		j++;
	}
	arr[j] = 0;
	return arr;
}
