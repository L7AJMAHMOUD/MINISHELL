/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:50:19 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/07 09:57:38 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_shearch(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (haystack && haystack[i] && haystack[i] != 32)
	{
		if (haystack[i] != needle[j])
			return 0;
		i++;
		j++;
	}
	if (needle[i] == '=')
		return &needle[i];
	return 0;
}

int ft_check(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i++] != 'n')
			return 0;
	}
	return 1;
}

void print(char *str)
{
	int i;
	i = 0;

	while (str && str[i])
	{
		if (str[i++] == '=')
			while(str[i])
				write(1, &str[i++], 1);
	}
}

void	priint(char *str, int k)
{
	int i;

	i = 0;
	while(str && str[i])
	{
		if (str[i] == '=')
			i++;
		if (str[i] == '$' && (str[i + 1] <= '9' && str[i + 1] >= '0'))
			i += 2;
		if (str[i] == '$' && (str[i + 1] > '9' || str[i + 1] < '0'))
			break;
		write(1, &str[i], 1);
		i++;
	}
	if (k != 0)
		write(1, " ", 1);
}
void echo(char **str, int fd, char **envp)
{
	int i;
	int j;
	int k;
	int p;
	int b;
	char *tmp;

	i = 1;
	k = 0;
	p = 0;
	j = 0;
	if (str && str[i] && ft_check(str[i]))
	{
		i++;
		p = -1;
	}
	while(str && str[i])
	{
		while (str[i][j] == '=')
			write(1, &str[i][j++], 1);
		if (str[i][j] == '$')
		{
			if (k == 1)
				break ;
			k = 1;
			j++;
			if (str[i][j] <= '9' && str[i][j] >= '0')
			{
				print(&str[i][++j]);
			}
			else if(ft_isalpha(str[i][j]))
			{
				b = 0;
				while(envp[b])
				{
					tmp = ft_shearch(&str[i][j], envp[b++]);
					if (tmp)
					{
						
						if (str[i + 1])
							priint(tmp, 1);
						else
							priint(tmp, 0);
						break ;
					}
				}
			}
		}
		else
		{
			if (str[i + 1])
				priint(str[i], 1);
			else
				priint(str[i], 0);
		}
		i++;
		if (!str[i] && p == 0)
			write(1, "\n", 1);
	}
}


void	pwd(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D')
			break ;
		i++;
	}
	if (!envp[i])
        ft_print("pwd not disponible\n", 0);
	else
    	printf("%s\n",&envp[i][4]);
}

