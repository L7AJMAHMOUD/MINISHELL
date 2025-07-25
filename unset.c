/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:11:38 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/24 21:44:38 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	comp(char **envp, char *ligne, t_indexes *indx, char **str)
{
	indx->i = 0;
	if (indx->j != indx->m || is_prefix_equal_until_equal_sign(envp[indx->m], ligne))
	{
		str[indx->k] = malloc(ft_strlen(envp[indx->j]) + 1);
		if (!str[indx->k])
			return (free_all_ul_split(str), 1);
		while (envp[indx->j][indx->i])
		{
			str[indx->k][indx->i] = envp[indx->j][indx->i];
			indx->i++;
		}
		str[indx->k++][indx->i] = 0;
	}
	indx->j++;
	return (0);
}

char	**rm_to_envp(char **envp, char *ligne)
{
	t_indexes	indx;
	char		**str;

	indx.j = 0;
	indx.k = 1;
	if (!envp || !ligne)
		return (NULL);
	indx.m = find_env_var_index(envp, ligne, &indx.k);
	if (indx.m == -1)
		return (envp);
	while (envp[indx.j])
		indx.j++;
	str = malloc((indx.j) * sizeof(char *));
	if (!str)
		return (NULL);
	indx.j = 0;
	indx.k = 0;
	while (envp[indx.j])
		if (comp(envp, ligne, &indx, str))
			return (NULL);
	str[indx.k] = NULL;
	return (free_all_ul_split(envp), str);
}

void	unset(char ***envp, char **command, t_data *data)
{
	int		j;
	char	**tmp;

	j = 1;
	data->status = 0;
	while (command[j])
	{
		if (!ft_strcmp("PATH", command[j]))
		{
			free(data->path);
			data->path = NULL;
		}
		tmp = rm_to_envp(*envp, command[j++]);
		if (tmp)
			*envp = tmp;
	}
}
