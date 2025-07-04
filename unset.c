/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:11:38 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/04 18:37:54 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int analyse_c(char **envp, char *ligne, int *k)
{
	int i;
	int j;

	i = 0;
	while (envp[i])
	{
		j  = 0;
		if (!ft_str_cmp(envp[i], ligne))
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
	if (s1[i] == '=' && s2[i] != '=')
		return 0;
	return 1;
}

char **rm_to_envp(char **envp, char *ligne)
{
    int i;
    int j;
    int k;
    int m;
    char **str;

    j = 0;
	k = 1;
	if (!envp || !ligne)
		return NULL;
	m = analyse_c(envp, ligne, &k);
	if (m == -1)
	{
		printf ("heloo   %d\n",k);
		return envp;
	}
    while (envp[j])
        j++;
    str = malloc((j) * sizeof(char *));
    j = 0;
	k = 0;
    while(envp[j])
    {
        i = 0;
		if (j != m || analyse_d(envp[m], ligne))
		{
			str[k] = malloc(ft_strlen(envp[j]) + 1);
			while(envp[j][i])
			{
				str[k][i] = envp[j][i];
				i++;
			}
			str[k][i] = 0;
			k++;
		}
        j++;
    }
    str[k] = NULL;
    free_all_ul_split(envp);
    return str;
}

void unset(char ***envp, char **command)
{
    int i;
    int j;
    char **tmp;
    int k;

    i = 0;
    j = 1;
	while(command[j])
		*envp = rm_to_envp(*envp, command[j++]);
}
