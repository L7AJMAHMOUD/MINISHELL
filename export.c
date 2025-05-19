/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:11:38 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/19 10:54:25 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_cmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if (s1[i] == '=' && !s2[i] || s2[i] == '=' && !s1[i])
		return 0;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

int analyse_c(char **envp, char *ligne, int *k)
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
	return 0;
}

int analyse_d(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if (s1[i] == '=' && s2[i] != '=')
		return 0;
	return 1;
}

char **add_to_envp(char **envp, char *ligne)
{
    int i;
    int j;
    int k;
    int m;
    char **str;

    j = 0;
	k = 2;
	if (!envp)
		return NULL;
	m = analyse_c(envp, ligne, &k);
    while (envp[j])
        j++;
    str = malloc((j + k) * sizeof(char *));
    j = 0;
    while(envp[j])
    {
        i = 0;
		if (k == 1 && j == m && analyse_d(envp[m], ligne))
		{
			str[j] = malloc(ft_strlen(ligne) + 1);
			while(ligne[i])
			{
				str[j][i] = ligne[i];
				i++;
			}
			str[j][i] = 0;
		}
		else
		{
			str[j] = malloc(ft_strlen(envp[j]) + 1);
			while(envp[j][i])
			{
				str[j][i] = envp[j][i];
				i++;
			}
			str[j][i] = 0;
		}
        j++;
    }
    i = 0;
	if (k == 2)
	{
		str[j] = malloc(ft_strlen(ligne) + 1);
		while(ligne[i])
		{
			str[j][i] = ligne[i];
			i++;
		}
		str[j++][i] = 0;
	}
    str[j] = NULL;
    free_all_ul_split(envp);
    return str;
}

int	check_synt(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == '"')
		i++;	
	if (!ft_isalpha(str[i]) && str[i] != '\\')
		return (ft_print("minishell: export: not a valid identifier ​😉", 0), 1);
	return 0;
}
void export(char ***envp, char **command)
{
    int i;
    int j;
    char **tmp;
    int k;

    i = 0;
    j = 1;
    tmp = *envp;
    if (!command[1])
        while (tmp[i])
        {
            j = 0;
            k = 0;
            write(1, "declare -x ", 12); 
            while(tmp[i][j])
            {
                write(1, &tmp[i][j], 1);
                if (tmp[i][j] == '=' || (!tmp[i][j + 1] && k == 1))
                {
                    write(1, "\"", 1);
                    k = 1;
                }
                j++;
            }
            write(1, "\n", 1);
            i++;
        }
    else
    {
        while(command[j])
        {
			if (check_synt(command[j]))
				break;
            tmp = add_to_envp(*envp, command[j++]);
            *envp = tmp;
        }
    }
        
}

