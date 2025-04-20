/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:54:55 by abkaram           #+#    #+#             */
/*   Updated: 2025/04/20 09:00:31 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_an(char *haystack, char *needle)
{
	size_t	i;

	i = 0;
	while (haystack[i] == needle[i] && haystack[i])
		i++;
	if (i == ft_strlen(needle))
		return (1);
	return (0);
}

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == 0)
		return (haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[j])
			if (ft_an(&haystack[i], needle) == 1)
				return (&haystack[i + 2]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	k;
	size_t	j;
	char	*str;

	j = 0;
	k = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (str == NULL)
		return (0);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	str[j++] = 32;
	while (s2[k])
		str[j++] = s2[k++];
	str[j] = '\0';
	return (free(s1), free(s2), str);
}
char	*ft_strdup(char *src )
{
	size_t	i;
	char	*h;

	i = 0;
	h = malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!h)
		return (0);
	while (src[i])
	{
		h[i] = src[i];
		i++;
	}
	h[i] = '\0';
	return (h);
}
