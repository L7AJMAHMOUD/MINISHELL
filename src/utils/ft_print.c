/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:36:10 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/05 13:02:21 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_putchar(char s)
{
	return (write (2, &s, 1));
}

static int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		i += ft_putchar(s[i]);
	}
	return (i);
}

static int	ft_putnbr(int n)
{
	char	c;
	int		i;

	i = 0;
	if (n == -2147483648)
		i += ft_putstr("-2147483648");
	else if (n < 0)
	{
		write(2, "-", 1);
		i += ft_putnbr(-n) + 1;
	}
	else if (n >= 0 && n < 10)
	{
		c = (n + 48);
		i += ft_putchar(c);
	}
	else if (n >= 10)
	{
		i += ft_putnbr(n / 10);
		i += ft_putnbr(n % 10);
	}
	return (i);
}

void	ft_print(char *s, int i)
{
	ft_putstr(s);
	if (i != 0)
	{
		ft_putstr(" : ");
		ft_putnbr(i);
	}
	ft_putchar('\n');
}