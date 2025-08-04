/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:25:16 by abkaram           #+#    #+#             */
/*   Updated: 2025/08/04 19:25:17 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
