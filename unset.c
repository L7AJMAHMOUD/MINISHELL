/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:11:38 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/16 11:27:34 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int analyse_c(char **envp, char *ligne, int *k)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!strcmp_until_equal(envp[i], ligne))
		{
			*k = 1;
			return i;
		}
		i++;
	}
	return -1;
}

static int analyse_d(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if ((s1[i] == '=' && s2[i] != '=') || (!s1[i] && !s2[i]))
		return 0;
	return 1;
}

int comp(char **envp, char *ligne, t_indexes *indx, char **str)
{
	indx->i = 0;
	if (indx->j != indx->m || analyse_d(envp[indx->m], ligne))
	{
		str[indx->k] = malloc(ft_strlen(envp[indx->j]) + 1);
		if (!str[indx->k])
			return(free_all_ul_split(str), 1);
		while(envp[indx->j][indx->i])
		{
			str[indx->k][indx->i] = envp[indx->j][indx->i];
			indx->i++;
		}
		str[indx->k++][indx->i] = 0;
	}
	indx->j++;
    return 0;
}

char **rm_to_envp(char **envp, char *ligne)
{
    t_indexes indx;
    char **str;

    indx.j = 0;
	indx.k = 1;
	if (!envp || !ligne)
		return NULL;
	indx.m = analyse_c(envp, ligne, &indx.k);
	if (indx.m == -1)
		return envp;
    while (envp[indx.j])
        indx.j++;
    str = malloc((indx.j) * sizeof(char *));
	if (!str)
		return NULL;
    indx.j = 0;
	indx.k = 0;
    while(envp[indx.j])
        if (comp(envp, ligne, &indx, str))
			return NULL;
    str[indx.k] = NULL;
    return (free_all_ul_split(envp), str);
}

void unset(char ***envp, char **command, t_data *data)
{
    int j;
	char **tmp;

    j = 1;
	data->status = 0;
	while(command[j])
	{
		if (!ft_strcmp("PATH",command[j]))
		{
			free(data->path);
			data->path = NULL;
		}
		tmp = rm_to_envp(*envp, command[j++]);
		if (tmp)
			*envp = tmp;
	}
}
