/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:11:38 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/13 10:47:02 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_cmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if ((s1[i] == '=' && !s2[i]) || (s2[i] == '=' && !s1[i]))
		return 0;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

int analyse_c(char **envp, char *ligne, int *k)
{
	int i;

	i = 0;
	while (envp[i])
	{
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

char **add_to_envp(char **envp, char *ligne, int p)
{
	int i, j, k, m;
	char **str;

	if (!envp || !ligne)
		return NULL;

	k = 2;
	m = analyse_c(envp, ligne, &k);
	if (p == 1 && k == 2)
		return envp;

	j = 0;
	while (envp[j])
		j++;

	str = malloc((j + k) * sizeof(char *));
	if (!str)
		return envp;

	j = 0;
	while (envp[j])
	{
		i = 0;
		if (k == 1 && j == m && analyse_d(envp[m], ligne))
		{
			str[j] = malloc(ft_strlen(ligne) + 1);
			if (!str[j])
				return free_all_ul_split(str), envp;
			while (ligne[i])
			{
				str[j][i] = ligne[i];
				i++;
			}
			str[j][i] = '\0';
		}
		else
		{
			str[j] = malloc(ft_strlen(envp[j]) + 1);
			if (!str[j])
				return free_all_ul_split(str), envp;
			while (envp[j][i])
			{
				str[j][i] = envp[j][i];
				i++;
			}
			str[j][i] = '\0';
		}
		j++;
	}

	if (k == 2)
	{
		i = 0;
		str[j] = malloc(ft_strlen(ligne) + 1);
		if (!str[j])
			return free_all_ul_split(str), envp;
		while (ligne[i])
		{
			str[j][i] = ligne[i];
			i++;
		}
		str[j++][i] = '\0';
	}
	str[j] = NULL;
	free_all_ul_split(envp);
	return str;
}


char **copy_envp(char **envp)
{
	int i;
	int j;
	char **str;

	if (!envp)
		return NULL;

	j = 0;
	while (envp[j])
		j++;

	str = malloc((j + 1) * sizeof(char *));
	if (!str)
		return NULL;

	j = 0;
	while (envp[j])
	{
		i = 0;
		str[j] = malloc(ft_strlen(envp[j]) + 1);
		if (!str[j])
		{
			free_all_ul_split(str);
			return NULL;
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
	return str;
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
	return 0;
}


void ft_swap_str(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
	
}

char **arr_sorted(char **str)
{
	int i, j;
	char **tmp;

	if (!str)
		return NULL;

	tmp = copy_envp(str);
	if (!tmp)
		return NULL;

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
	return tmp;
}
char *command_analyse(char *command, char **envp)
{
	int i;
	char *str;
	char *tmp;
	char *cmd;

	cmd = NULL;
	i = 0;
	if (!command || !envp)
		return NULL;
	while (command[i] && command[i] != '+' && command[i] != '=')
	{
		i++;
	}
	if (!command[i] || command[i] == '=')
		return command;
	tmp = ft_strdup(&command[i + 2]);
	command[i] = 0;
	str = get_variable(command, envp);
	cmd = strjoin(cmd, command);
	free(command);
	cmd = strjoin(cmd, "=");
	cmd = strjoin(cmd, str);
	cmd = strjoin(cmd, tmp);
	return cmd;
}

void export(char ***envp, char **command, t_data *data)
{
    int i;
    int j;
    char **tmp;
    int k;

    i = 0;
    j = 1;
    if (!command[1])
	{
		tmp = arr_sorted(*envp);////////////
		if (!tmp)
		{
			data->status = 1;
			return ;
		}
        while (tmp[i])
        {
            j = 0;
            k = 0;
            write(1, "declare -x ", 12); 
            while(tmp[i][j])
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
                j++;
				if (k == 1 && !tmp[i][j])
					write(1, "\"", 1);
            }
            write(1, "\n", 1);
            i++;
        }
		data->status = 0;
		free_all_ul_split(tmp);
	}
    else
    {
		data->status = 0;
        while(command[j])
        {
			if (check_synt(command[j]))
			{
				data->status = 1;
				j++;
				continue;
			}
			command[j] = command_analyse(command[j], *envp);
            tmp = add_to_envp(*envp, command[j++], 0);//////////////
            *envp = tmp;
        }
    }
}

