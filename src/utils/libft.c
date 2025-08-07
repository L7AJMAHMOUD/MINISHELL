/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:15:47 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:15:48 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

static int	norm(int n)
{
	if (n == -1)
		return (-1);
	return (-1);
}

long	ft_atoi(const char *str)
{
	int			i;
	long double	m;
	int			n;

	n = 1;
	i = 0;
	m = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		m = (m * 10) + (str[i] - 48);
		if (m > 9223372036854775807)
			return (norm(n));
		i++;
	}
	return (n * (long) m);
}

char	*join_strings(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*loc;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	loc = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!loc)
		return (NULL);
	while (s1[i])
		loc[j++] = s1[i++];
	i = 0;
	while (s2[i])
		loc[j++] = s2[i++];
	loc[j] = '\0';
	return (loc);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
