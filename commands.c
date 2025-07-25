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

int is_echo_n_flag(char *str)
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


void	print_env_value_escaped(char *str, int k)
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
void echo(char **str, t_data *data)
{
	int i;
	int j;
	int p;

	i = 1;
	p = 0;
	j = 0;
	while (str && str[i] && is_echo_n_flag(str[i]))
	{
		i++;
		p = -1;
	}
	while(str && str[i])
	{
		while (str[i][j] == '=')
			write(1, &str[i][j++], 1);
		if (str[i + 1])
			print_env_value_escaped(str[i], 1);
		else
			print_env_value_escaped(str[i], 0);
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
