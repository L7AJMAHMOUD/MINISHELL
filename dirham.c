/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirham.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 06:00:23 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/07 11:26:05 by abkaram          ###   ########.fr       */
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
	if (!str)
		return NULL;
	i = 0;
	while (stro[i])
	{
		j = 0;
		while(stro[i][j] == 32)
			j++;
		len = ft_strlen(&stro[i][j]);
		str[i] = malloc(len + 1);
		if (!str[i])
		{
			for (int l = 0; l < i; l++)
				free(str[l]);
			return NULL;
		}
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
	char **str;
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
	str = ft_regenerate_2arr(stro);
	free_all_ul_split(stro);
	return (str);
}

int ft_strlen_(char *stro)
{
	int i;
	int j;

	i = 0;
	j = 0;
	
	if (!stro)
		return 0;
	while(stro[i])
	{
		if (stro[i] == '$')
		{
			i++;
			j++;
			while (stro[i] != 32 && stro[i])
			{
				i++;
				j++;
			}
			
		}
		else
			i++;
	}
	return (i - j);
	
}

char **regenerat_dol_with_env(char **stro, char *comm, int k)
{
	char **str;
	int i;
	int j;
	int x = 0;
	int len;

	i = 0;
	while(stro[i])
		i++;
	str = malloc ((i + 1) * sizeof(char *));
	if (!str)
		return NULL;
	i = 0;
	while (stro[i])
	{
		j = 0;
		if (i == k)
		{
			while(comm[j] != '=')
				j++;
			len = ft_strlen(&comm[++j] + ft_strlen_(stro[i]));
			str[i] = malloc(len + 1);
			if (!str[i])
			{
				for (int l = 0; l < i; l++)
					free(str[l]);
				return NULL;
			}
			len = 0;
			while (stro[i][x])
			{
				if (stro[i][x] == '$')
				{
					while(comm[j])
						str[i][len++] = comm[j++];
					while(stro[i][x] != 32 && stro[i][x])
						x++;
				}
				str[i][len++] = stro[i][x++];
			}
			str[i][len] = 0;
		}
		else
		{
			if (stro[i][j] <= 57 && stro[i][j] >= 48)
				j++;
			len = ft_strlen(&stro[i][j]);
			str[i] = malloc(len + 1);
			len = 0;
			while(stro[i][j])
				str[i][len++] = stro[i][j++];
			str[i][len] = 0;
		}
		i++;
	}
	str[i] = 0;
	free_all_ul_split(stro);
	return str;	
}

char **regenerat_dol_with_env_emply(char **stro, int k)
{
    char **str;
    int i = 0, j, z = 0, len, x= 0;
    while (stro[i])
        i++;
    str = malloc((i + 1) * sizeof(char *));
    if (!str)
        return NULL;
    i = 0;
    while (stro[i])
    {
        if (i == k) {
			// str[i] = malloc(ft_strlen_(stro[i]) + 1);
			// if (!str[i])
			// {
			// 	for (int l = 0; l < i; l++)
			// 		free(str[l]);
			// 	return NULL;
			// }
			// len = 0;
			// x = 0;
			// while (stro[i][x])
			// {
			// 	if (stro[i][x] == '$')
			// 	{
			// 		while(stro[i][x] != 32 && stro[i][x])
			// 			x++;
			// 	}
			// 	else
			// 		str[i][len++] = stro[i][x++];
			// }
			// str[i][len] = 0;
            i++;
			// z++;
            continue;
        }
        j = 0;
        if (stro[i][j] >= '0' && stro[i][j] <= '9')
            j++;
        len = strlen(&stro[i][j]);
        str[z] = malloc(len + 1);
        if (!str[z])
            return NULL;
        len = 0;
        while(stro[i][j])
            str[z][len++] = stro[i][j++];
        str[z][len] = 0;
        z++;
        i++;
    }
    str[z] = NULL;
	free_all_ul_split(stro);
    return str;
}


char **dirham(char **st, char **envp)
{
	int i;
	int j;
	int o;
	int b;
	char *tmp;
	char **str;

	str = read_stock(st);

	i = 0;
	
	while (str[i])
	{
		j  = 0;
		while (str[i][j])
		{
			o = 0;
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
					st = regenerat_without_dol(st);
					if (!st)
						return NULL;
					return(dirham(st,envp));
				}
				else
				{
					while(envp[b])
					{
						tmp = ft_shearch(&str[i][j], envp[b++]);
						if (tmp)
						{
							st = regenerat_dol_with_env(st, envp[b - 1], i);
							b = -1;
							if (!st)
								return NULL;
							return(dirham(st,envp));
						}
					}
				}
				if (b != -1)
				{
					st = regenerat_dol_with_env_emply(st, i);
					if (!st)
						return NULL;
					while (str[i][j] && str[i][j + 1] != '$')
						j++;
				}
			}
			if (str[i][j])
				j++;
		}
		i++;
	}
	free_all_ul_split(str);
	return st;
}
