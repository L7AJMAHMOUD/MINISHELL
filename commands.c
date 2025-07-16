/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:50:19 by abkaram           #+#    #+#             */
/*   Updated: 2025/06/04 08:54:14 by abkaram          ###   ########.fr       */
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

	i = 0;
	if (str[i++] != '-')
		return 0;
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
	int l;

	i = 0;
	l = 0;
	while(str && str[i])
	{
		if (str[i] == '=')
			i++;
		if (str[i] == '\\')
		{
			i++;
			l++;
			if (str[i] != '\\')
			{
					l /= 2;
				while (l > 0)
				{
					l--;
					write(1, "\\", 1);
				}
			}
		}
		write(1, &str[i], 1);
		i++;
	}
	if (k != 0)
		write(1, " ", 1);
}
void echo(char **str, int fd, char **envp, t_data *data)
{
	int i;
	int j;
	int k;
	int p;
	int o;
	int b;
	char *tmp;

	i = 1;
	k = 0;
	p = 0;
	j = 0;
	while (str && str[i] && ft_check(str[i]))
	{
		i++;
		p = -1;
	}
	while(str && str[i])
	{
		while (str[i][j] == '=')
			write(1, &str[i][j++], 1);
		if (str[i + 1])
			priint(str[i], 1);
		else
			priint(str[i], 0);
		i++;
		if (!str[i] && p == 0)
			write(1, "\n", 1);
	}
	data->status = 0;
}


void	pwd(t_data *data)
{
	char buff[BUFFER_SIZE];

	if(!getcwd(buff,BUFFER_SIZE))
	{
		data->status = 0;
		printf("%s\n",data->pwd);
		return ;
	}
	data->status = 0;
	printf("%s\n",buff);
}
