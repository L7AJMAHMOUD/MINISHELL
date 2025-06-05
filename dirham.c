/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirham.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 06:00:23 by abkaram           #+#    #+#             */
/*   Updated: 2025/06/05 09:24:43 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ //

char **ft_regenerate_2arr(char **stro)
{
	char **str;
	int i;
	int j;
	int len;

	i = 0;
	while(stro[i])
		i++;
	str = malloc ((i + 1) * sizeof(char *));
	i = 0;
	while (stro[i])
	{
		j = 0;
		while(stro[i][j] == 32)
			j++;
		len = ft_strlen(&stro[i][j]);
		str[i] = malloc(len + 1);
		len = 0;
		while(stro[i][j])
			str[i][len++] = stro[i][j++];
		str[i][len] = 0;
		i++;
	}
	str[i] = 0;
	return str;	
}

char **regenerat_without_dol(char **stro)
{
	char ***str;
	int i;
	int j;

	i = 0;
	while(stro[i])
	{
		j = 0;
		while (stro[i][j] == '$')
			stro[i][j++] = 32;
		if (stro[i][j] <= 57 && stro[i][j] >= 48)
			stro[i][j++] = 32;
		if (j != 0)
			break;
		i++;
	}
	*str = ft_regenerate_2arr(stro);
	free_all_ul_split(stro);
	return (*str);
}
char **regenerat_dol_with_env(char **stro, char *comm, int k)
{
	char **str;
	int i;
	int j;
	int z;
	int len;

	i = 0;
	z = 0;
	while(stro[i])
		i++;
	// if (!comm)
	// 	i--;
	str = malloc ((i + 1) * sizeof(char *));
	i = 0;
	while (stro[i])
	{
		j = 0;
		if (i == k)
		{
			if (!comm)
				z++;
			else
			{
				while(comm[j] != '=')
					j++;
				len = ft_strlen(&comm[++j]);
				str[i] = malloc(len + 1);
				len = 0;
				while(comm[j])
					str[i][len++] = comm[j++];
				str[i][len] = 0;
			}
		}
		else
		{
			if (stro[i + z][j] <= 57 && stro[i + z][j] >= 48)
				j++;
			len = ft_strlen(&stro[i + z][j]);
			str[i] = malloc(len + 1);
			len = 0;
			while(stro[i + z][j])
				str[i][len++] = stro[i + z][j++];
			str[i][len] = 0;
		}
		i++;
	}
	str[i] = 0;
	return str;	
}

char **dirham(char ***st, char **envp)
{
	int i;
	int j;
	int o;
	int b;
	char *tmp;
	char **str;

	str = *st;

	i = 0;
	o = 0;
	while (str[i])
	{
		j  = 0;
		while (str[i][j])
		{
			b = 0;
			if (str[i][j] == '$' && str[i][j + 1] != 32 && str[i][j + 1])
			{
				while(str[i][j] == '$')
				{
					j++;
					o++;
					if (str[i][j] != '$')
					{
						if (o % 2)
							o = -1;
					}
				}
				if (o != -1 || (str[i][j] <= 57 && str[i][j] >= 48))
				{
					*st = regenerat_without_dol(*st);
					break;
				}
				else
				{
					while(envp[b])
					{
						tmp = ft_shearch(&str[i][j], envp[b++]);
						if (tmp)
						{
							*st = regenerat_dol_with_env(*st, envp[b - 1], i);
							b = -1;
							break;
						}
					}
				}
				if (b != -1)
				{
					*st = regenerat_dol_with_env(*st, NULL, i);
					break;
				}
			}
			j++;
		}
		i++;
	}
	return *st;
}
