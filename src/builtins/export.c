/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:11:38 by abkaram           #+#    #+#             */
/*   Updated: 2025/08/04 22:12:23 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**copy_envp(char **envp)
{
	char	**str;
	int		j;

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
		str[j] = dup_env_line(envp[j]);
		if (!str[j])
			return (free_all_ul_split(str), NULL);
		j++;
	}
	return (str[j] = NULL, str);
}

static int	check_synt(char *str)
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
		{
			ft_print("minishell: export: not a valid identifier", 0);
			return (1);
		}
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

void	print_env_export(char **tmp, int j)
{
	int	i;
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
				if (k == 1)
					k = -1;
				else
					k = 1;
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
		print_env_export(tmp, 0);
		free_all_ul_split(tmp);
		return ((void)(data->status = 0));
	}
	data->status = 0;
	while (cmd[j])
	{
		if (check_synt(cmd[j++]))
			data->status = 1;
		tmp = add_to_envp(*envp, command_analyse(cmd[j - 1], *envp, data),
				0, NULL);
		*envp = tmp;
	}
}
