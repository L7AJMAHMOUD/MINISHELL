/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:32:43 by abkaram           #+#    #+#             */
/*   Updated: 2025/08/04 22:18:20 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strmerge_and_free(char *s1, char *s2)
{
	size_t	k;
	size_t	j;
	char	*str;

	j = 0;
	k = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (0);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	while (s2[k])
		str[j++] = s2[k++];
	str[j] = '\0';
	free(s1);
	return (s1 = NULL, str);
}

void	update_pwd_vars(char *buff, t_data *data, char ***envp)
{
	char	**tmp;
	char	*command;

	command = strmerge_and_free(ft_strdup("OLDPWD="), data->pwd);
	free(data->pwd);
	tmp = add_to_envp(*envp, command, 1, NULL);
	free(command);
	*envp = tmp;
	data->pwd = ft_strdup(buff);
	command = strmerge_and_free(ft_strdup("PWD="), data->pwd);
	tmp = add_to_envp(*envp, command, 1, NULL);
	free(command);
	*envp = tmp;
}

int	complete(char ***envp, char **arg, t_data *data, char **tmp)
{
	char	buff[BUFFER_SIZE];
	DIR		*dir;
	int		i;

	if (!arg || !arg[0])
	{
		*tmp = get_variable("HOME", *envp, data);
		if (!*tmp || chdir(*tmp) != 0)
			return (data->status = 1,
				ft_print("minishell: HOME not set", 0), 1);
		return (update_pwd_vars(buff, data, envp), 1);
	}
	i = 0;
	*tmp = strmerge_and_free(*tmp, arg[i]);
	dir = opendir(*tmp);
	if (!dir || arg[i + 1])
	{
		if (arg[i + 1])
		{
			ft_print("minishell: cd: too many arguments", 0);
			return (free(*tmp), data->status = 2, 1);
		}
		return (data->status = 1, perror("minishell"), 1);
	}
	return (closedir(dir), 0);
}

void	cd(char ***envp, char **arg, t_data *data)
{
	char	buff[BUFFER_SIZE];
	char	*str;
	char	*tmp;

	tmp = NULL;
	if (complete(envp, arg, data, &tmp))
		return ;
	chdir(tmp);
	free(tmp);
	data->status = 0;
	str = getcwd(buff, BUFFER_SIZE);
	if (str)
		return (update_pwd_vars(buff, data, envp));
	perror("cd : erreur de détermination du répertoire actuel : \
getcwd : ne peut accéder aux répertoires parents ");
	data->status = 1;
	data->pwd = strmerge_and_free(data->pwd, "/..");
}
