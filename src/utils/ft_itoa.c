/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:16:27 by abkaram           #+#    #+#             */
/*   Updated: 2025/08/04 19:03:37 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	**cpt_read_stock(char **str, t_data *data)
{
	int	j;

	j = 0;
	str = malloc((3 + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str[j++] = ft_strdup("OLDPWD");
	str[j++] = join_strings("PWD", data->pwd);
	str[j++] = ft_strdup("SHLVL=1");
	str[j] = 0;
	return (str);
}

char	**read_stock(char **envp, t_data *data, int j, int i)
{
	char	**str;

	str = NULL;
	if (!envp[0])
		return (cpt_read_stock(str, data));
	while (envp[j])
		j++;
	str = malloc((j + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	j = 0;
	while (envp[j])
	{
		i = 0;
		str[j] = malloc(ft_strlen(envp[j]) + 1);
		if (!str[i])
			return (free_all_ul_split(str), NULL);
		while (envp[j][i])
		{
			str[j][i] = envp[j][i];
			i++;
		}
		str[j++][i] = 0;
	}
	return (str[j] = 0, str);
}
