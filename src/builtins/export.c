/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:11:38 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/27 22:03:26 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strcmp_until_equal(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if ((s1[i] == '=' && !s2[i]) || (s2[i] == '=' && !s1[i]))
		return (0);
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

int	find_env_var_index(char **envp, char *ligne, int *k)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strcmp_until_equal(envp[i], ligne))
		{
			*k = 1;
			return (i);
		}
		i++;
	}
	return (0);
}

int	is_prefix_equal_until_equal_sign(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if ((s1[i] == '=' && s2[i] != '=') || (!s1[i] && !s2[i]))
		return (0);
	return (1);
}

int	envp_array_length(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	duplicate_line_to_array(char **str, char *ligne, t_indexes *indx)
{
	str[indx->j] = malloc(ft_strlen(ligne) + 1);
	if (!str[indx->j])
		return (free_all_ul_split(str), 1);
	while (ligne[indx->i])
	{
		str[indx->j][indx->i] = ligne[indx->i];
		indx->i++;
	}
	str[indx->j][indx->i] = '\0';
	return (0);
}

int	duplicate_envp_entry(char **str, char **envp, t_indexes *indx)
{
	str[indx->j] = malloc(ft_strlen(envp[indx->j]) + 1);
	if (!str[indx->j])
		return (free_all_ul_split(str), 1);
	while (envp[indx->j][indx->i])
	{
		str[indx->j][indx->i] = envp[indx->j][indx->i];
		indx->i++;
	}
	str[indx->j][indx->i] = '\0';
	return (0);
}

int	duplicate_line_and_increment_index(char **str, char *ligne, t_indexes *indx)
{
	indx->i = 0;
	str[indx->j] = malloc(ft_strlen(ligne) + 1);
	if (!str[indx->j])
		return (free_all_ul_split(str), 1);
	while (ligne[indx->i])
	{
		str[indx->j][indx->i] = ligne[indx->i];
		indx->i++;
	}
	str[indx->j++][indx->i] = '\0';
	return (0);
}

int	initialize_indexes_and_find_env(char **envp, char *ligne, t_indexes *indx, int p)
{
	if (!envp)
		return (1);
	indx->p = p;
	indx->k = 2;
	indx->m = find_env_var_index(envp, ligne, &indx->k);
	indx->j = 0;
	if (indx->p == 1 && indx->k == 2)
		return (1);
	return (0);
}

char	**add_to_envp(char **envp, char *ligne, int p)
{
	t_indexes	indx;
	char		**str;

	if (!ligne || initialize_indexes_and_find_env(envp, ligne, &indx, p))
		return (envp);
	str = malloc((envp_array_length(envp) + indx.k) * sizeof(char *));
	if (!str)
		return (envp);
	while (envp[indx.j])
	{
		indx.i = 0;
		if (indx.k == 1 && indx.j == indx.m && is_prefix_equal_until_equal_sign(envp[indx.m], ligne))
		{
			if (duplicate_line_to_array(str, ligne, &indx))
				return (envp);
		}
		else
		{
			if (duplicate_envp_entry(str, envp, &indx))
				return (envp);
		}
		indx.j++;
	}
	if (indx.k == 2)
	{
		if (duplicate_line_and_increment_index(str, ligne, &indx))
			return (envp);
	}
	return (free_all_ul_split(envp), str[indx.j] = NULL, str);
}

char	**copy_envp(char **envp)
{
	int		i;
	int		j;
	char	**str;

	if (!envp)
		return (NULL);
	j = 0;
	while (envp[j])
		j++;
	str = malloc((j + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	j = 0;
	while (envp[j])
	{
		i = 0;
		str[j] = malloc(ft_strlen(envp[j]) + 1);
		if (!str[j])
		{
			free_all_ul_split(str);
			return (NULL);
		}
		while (envp[j][i])
		{
			str[j][i] = envp[j][i];
			i++;
		}
		str[j][i] = '\0';
		j++;
	}
	str[j] = NULL;
	return (str);
}

int	check_synt(char *str)
{
	int	i;

	if (!str || !str[0])
		return (ft_print("minishell: export: not a valid identifier", 0), 1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (ft_print("minishell: export: not a valid identifier", 0), 1);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ft_print("minishell: export: not a valid identifier", 0), 1);
		i++;
	}
	return (0);
}

void	ft_swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**arr_sorted(char **str)
{
	int		i;
	int		j;
	char	**tmp;

	if (!str)
		return (NULL);
	tmp = copy_envp(str);
	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i])
	{
		j = i + 1;
		while (tmp[j])
		{
			if (ft_strcmp(tmp[j], tmp[i]) < 0)
				ft_swap_str(&tmp[j], &tmp[i]);
			j++;
		}
		i++;
	}
	return (tmp);
}

char	*command_analyse(char *command, char **envp, t_data *data)
{
	int		i;
	char	*str;
	char	*tmp;
	char	*cmd;

	cmd = NULL;
	i = 0;
	if (!command || !envp)
		return (NULL);
	while (command[i] && command[i] != '+' && command[i] != '=')
	{
		i++;
	}
	if (!command[i] || command[i] == '=')
		return (command);
	tmp = ft_strdup(&command[i + 2]);
	command[i] = 0;
	str = get_variable(command, envp, data);
	cmd = strmerge_and_free(cmd, command);
	free(command);
	command = NULL;
	cmd = strmerge_and_free(cmd, "=");
	cmd = strmerge_and_free(cmd, str);
	cmd = strmerge_and_free(cmd, tmp);
	return (cmd);
}

void	print_env_export(char **tmp)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (tmp[++i])
	{
		j = -1;
		k = 0;
		write(1, "declare -x ", 11);
		while (tmp[i][++j])
		{
			write(1, &tmp[i][j], 1);
			if ((k == 0 && tmp[i][j] == '=') || (!tmp[i][j + 1] && k == 1))
			{
				write(1, "\"", 1);
				k = (k == 1) ? -1 : 1;
			}
		}
		if (k == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
}

void	export(char ***envp, char **cmd, t_data *data)
{
	char	**tmp;
	int		j;

	j = 1;
	if (!cmd[1])
	{
		tmp = arr_sorted(*envp);
		if (!tmp)
			return (data->status = 1, (void)0);
		print_env_export(tmp);
		free_all_ul_split(tmp);
		return ((void)(data->status = 0));
	}
	data->status = 0;
	while (cmd[j])
	{
		if (check_synt(cmd[j++]))
			return (data->status = 1, (void)0);
		tmp = add_to_envp(*envp, command_analyse(cmd[j - 1], *envp, data), 0);
		*envp = tmp;
	}
}