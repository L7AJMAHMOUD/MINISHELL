/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:16:27 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/16 12:26:38 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nbr_char(long n)
{
	long	i;
	long	j;

	i = 0;
	j = 1;
	if (n < 0)
	{
		j = 2;
		n = -n;
	}
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i + j);
}

static void	swp(char *h)
{
	size_t	i;
	size_t	j;
	char	c;

	j = ft_strlen(h) - 1;
	i = 0;
	if (h[i] == '-')
		i++;
	while (i < j)
	{
		c = h[i];
		h[i] = h[j];
		h[j] = c;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	long	m;
	char	c;
	char	*h;

	i = 0;
	m = n;
	h = malloc(nbr_char(n) * sizeof(char) + 1);
	if (!h)
		return (0);
	if (m < 0)
	{
		h[i++] = '-';
		m *= -1;
	}
	while (m >= 10)
	{
		c = (m % 10 + 48);
		h[i++] = c;
		m /= 10;
	}
	h[i] = (m + 48);
	h[i + 1] = '\0';
	swp(h);
	return (h);
}