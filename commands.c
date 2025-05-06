/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:50:19 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/06 16:35:48 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_an(char *haystack, char *needle, size_t k)
{
	size_t	i;

	i = 0;
	while (haystack[i] == needle[i] && haystack[i])
	{
		i++;
		k++;
	}
	if (i == ft_strlen(needle))
		return (1);
	return (0);
}

char	*ft_shearch(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack || !needle)
		return NULL;
	if (needle[j] == 0)
		return (haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[j])
			if (ft_an(&haystack[i], needle, i) == 1)
				return (&haystack[i]);
		i++;
	}
	return (0);
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

void	priint(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
	{
		if 
		if (str[i] == '$' && (str[i] > '9' || str[i] < '0'))
			i++;
		write(1, &str[i], 1);
		i++;
	}
}
void echo(char **str, int fd, char **envp)
{
	int i;
	int j;
	int k;
	char *tmp;

	i = 1;
	// if (str && str[i] && ft_check(str[i]))
	// {
	// 	i++;
	// 	while(str[i])
	// 	{
	// 		write(fd, str[i], ft_strlen(str[i]));
	// 		i++;
	// 	}
	// 	return ;
	// }
	k = 0;
	while(str && str[i])
	{
		if (str[i][0] == '$')
		{
			if (k == 1)
				break ;
			k = 1;
			if (str[i][1] <= '9' && str[i][1] >= '0')
			{
				print(&str[i][2]);
			}
			// else if(ft_isalpha(str[i][1]))
			// {
			// 	j = 0;
			// 	while(envp[j])
			// 	{
			// 		tmp = ft_shearch(envp[j++], &str[i][1]);
			// 		if (tmp)
			// 		{
			// 			print(tmp);
			// 			break;
			// 		}
			// 	}
			// }
		}
		else
			priint(str[i]);
			write(fd, " ", 1);
		i++;
	}
	write(fd, "\n", 1);
	
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

