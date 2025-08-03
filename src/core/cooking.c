/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:04:09 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/27 22:10:17 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_(char *s1, char *s2)
{
	size_t	k;
	size_t	j;
	char	*str;

	j = 0;
	k = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
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
	return (free(s1), s1 = NULL, free(s2), s2 = NULL, str);
}

void	free_commands_array(t_command *arr, int k)
{
	int	m;

	m = 0;
	while (m < k)
	{
		free(arr[m].command);
		arr[m++].command = NULL;
	}
	free(arr);
	arr = NULL;
}

int	allocate_next_command(t_command *arr, char *str, int *k, int j)
{
	arr[*k].command[j] = 0;
	*k += 1;
	arr[*k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[*k].command)
		return (free_arr(arr, *k - 1), 1);
	return (0);
}

int	complete_quoted_command(t_command *arr, char *str, t_indexes *ind)
{
	arr[ind->k].q = ind->c;
	while (str[ind->i] && str[ind->i] != ind->c)
		arr[ind->k].command[ind->j++] = str[ind->i++];
	if (str[ind->i] == ind->c)
		ind->i++;
	arr[ind->k].command[ind->j] = '\0';
	ind->k++;
	ind->j = 0;
	if (!str[ind->i])
	{
		arr[ind->k].command = NULL;
		arr->nbr = ind->k;
		return (2);
	}
	arr[ind->k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[ind->k].command)
		return (free_commands_array(arr, ind->k), 1);
	return (0);
}

int	handle_empty_quote_command(t_command *arr, t_indexes *indx, char *str)
{
	free(arr[indx->k].command);
	arr[indx->k].command = ft_strdup("''");
	if (!arr[indx->k].command)
		return (free_arr(arr, indx->k - 1), 1);
	indx->j = 0;
	indx->k++;
	arr[indx->k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[indx->k].command)
		return (free_commands_array(arr, indx->k), 1);
	return (0);
}

int	init_command_array(t_command **arr, t_indexes *indx, char *str)
{
	indx->c = 0;
	indx->i = 0;
	indx->j = 0;
	indx->k = 0;
	indx->p = 0;
	*arr = malloc(sizeof(t_command) * (ft_strlen(str) + 1));
	if (!arr)
		return (1);
	ft_memset(*arr, 0, sizeof(t_command) * (ft_strlen(str) + 1));
	(*arr)[indx->k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(*arr)[indx->k].command)
		return (free(arr), arr = NULL, 1);
	return (0);
}

t_command	*return_null_if_one(t_command *arr, int i)
{
	if (i == 1)
		return (NULL);
	return (arr);
}

int	init_quote_state(t_indexes *indx, char *str)
{
	indx->j = 0;
	indx->c = str[indx->i++];
	return (0);
}

t_command	*cleaning(char *str, int p, t_command *arr, t_indexes indx)
{
	if (init_command_array(&arr, &indx, str))
		return (NULL);
	while (str[indx.i])
	{
		if (str[indx.i] == QUOTE_SINGLE || str[indx.i] == QUOTE_DOUBLE)
		{
			if (indx.j != 0)
				if (allocate_next_command(arr, str, &(indx.k), indx.j))
					return (NULL);
			init_quote_state(&indx, str);
			if (indx.c == str[indx.i] && p == 0 && !str[indx.i + 1])
			{
				if (handle_empty_quote_command(arr, &indx, str))
					return (NULL);
				continue ;
			}
			indx.c = complete_quoted_command(arr, str, &indx);
			if (indx.c == 1 || indx.c == 2)
				return (return_null_if_one(arr, indx.c));
		}
		else
			arr[indx.k].command[indx.j++] = str[indx.i++];
	}
	arr[indx.k].command[indx.j] = '\0';
	return (arr[++indx.k].command = NULL, arr->nbr = indx.k, arr);
}

int	is_special_char(char c)
{
	return (c == '$' || c == '\'' || c == '\"' || c == ' ' || c == '\t'
		|| c == '<' || c == '>' || c == '!' || c == '?' || c == '='
		|| c == '+' || c == '-' || c == '/' || c == '|' || c == '&'
		|| c == ';' || c == '*' || c == '[' || c == ']' || c == '('
		|| c == ')' || c == '#' || c == '{' || c == '}');
}

int	strlen_until_special(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && !is_special_char(str[i]))
		i++;
	return (i);
}


char	*get_variable(char *str, char **envp, t_data *data)
{
	int		i;
	int		len;
	char	*equal_pos;

	i = 0;
	if (!str || !envp)
		return (NULL);
	len = strlen_until_special(str);
	while (envp[i])
	{
		if (strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
		{
			equal_pos = strchr(envp[i], '=');
			if (equal_pos)
				return (equal_pos + 1);
		}
		i++;
	}
	if (strcmp("PATH", str) == 0 && data->path)
		return (data->path);
	return (NULL);
}

void	expand_env_variable(t_command *arr,
			t_indexes indx, int *j, t_data *data)
{
	int		var_len;
	char	*varname;
	char	*val;
	char	*tmp;
	char	*str;

	var_len = strlen_until_special(&(arr[indx.i].command[*j]));
	varname = malloc(var_len + 1);
	if (!varname)
		return ;
	strncpy(varname, &(arr[indx.i].command[*j]), var_len);
	varname[var_len] = '\0';
	tmp = get_variable(varname, arr->envp, data);
	if (tmp)
		val = ft_strdup(tmp);
	else
		val = NULL;
	str = ft_strdup(&(arr[indx.i].command[*j + var_len]));
	arr[indx.i].command[*j - 1 - indx.p] = 0;
	arr[indx.i].command = ft_strjoin_(arr[indx.i].command, val);
	var_len = ft_strlen(arr[indx.i].command);
	arr[indx.i].command = ft_strjoin_(arr[indx.i].command, str);
	free(varname);
	*j = var_len;
}

void	expand_exit_status(t_command *arr, int i, int *j, int p)
{
	int		var_len;
	char	*varname;
	char	*val;
	char	*tmp;
	char	*str;

	var_len = 1;
	varname = malloc(var_len + 1);
	if (!varname)
		return ;
	strncpy(varname, &(arr[i].command[*j]), var_len);
	varname[var_len] = '\0';
	tmp = ft_itoa(arr->data->status);
	if (tmp)
		val = ft_strdup(tmp);
	else
		val = NULL;
	str = ft_strdup(&(arr[i].command[*j + var_len]));
	arr[i].command[*j - 1 - p] = 0;
	arr[i].command = ft_strjoin_(arr[i].command, val);
	var_len = ft_strlen(arr[i].command);
	arr[i].command = ft_strjoin_(arr[i].command, str);
	*j = var_len;
	free(varname);
}

void	remove_positional_parameter(t_command *arr, int i, int *p, int j)
{
	char	*str;

	if (arr[i].command[j] >= '0' && arr[i].command[j] <= '9')
		str = ft_strdup(&(arr[i].command[j + 1]));
	else
		str = ft_strdup(&(arr[i].command[j]));
	if (arr[i].command[j - (*p + 1)] == '$')
	{
		*p = *p + 1;
		arr[i].command[j - *p] = 0;
	}
	else
		arr[i].command[j - *p] = 0;
	arr[i].command = ft_strjoin_(arr[i].command, str);
}

void	skip_dollar_signs(t_command *arr, int *i, int *j, int *p)
{
	while (arr[*i].command[*j] == '$')
	{
		*j = *j + 1;
		*p = *p + 1;
	}
}

static void	helprs_handl_dol(int *p, int *m, int j)
{
	*p = 0;
	*m = j;
}

static void	helprs_handl_doll(t_indexes *indx, int p, int i)
{
	indx->i = i;
	indx->p = p;
}

static void	handle_positional(t_command *arr, int i, t_indexes *indxx, int *j)
{
	remove_positional_parameter(arr, i, &indxx->p, *j);
	*j = indxx->m;
}

void	handle_dollar(t_command *arr, int i, int j, t_data *data)
{
	t_indexes	indx;
	t_indexes	indxx;

	while (arr[i].command[j])
	{
		if (arr[i].command[j++] == '$')
		{
			helprs_handl_dol(&indxx.p, &indxx.m, j);
			skip_dollar_signs(arr, &i, &j, &indxx.p);
			if (arr[i].command[j] <= 32 && !arr[i + 1].command)
				continue ;
			if (arr[i].q == 39 || indxx.p % 2
				|| (arr[i].command[j] >= '0' && arr[i].command[j] <= '9'))
			{
				handle_positional(arr, i, &indxx, &j);
			}
			else if (arr[i].command[j] == '?')
				expand_exit_status(arr, i, &j, indxx.p);
			else
			{
				helprs_handl_doll(&indx, indxx.p, i);
				expand_env_variable(arr, indx, &j, data);
			}
		}
	}
}

void	expand(t_command *arr, t_data *data)
{
	int	i;

	i = 0;
	while (i < arr->nbr)
	{
		if (arr[i].q != 39)
			handle_dollar(arr, i, 0, data);
		if (arr[i].command[0] == 0 && arr[i].q == 0)
		{
			free(arr[i].command);
			arr[i].command = NULL;
		}
		i++;
	}
}

char	*ft_arr_to_str(t_command *arr)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (i < arr->nbr)
	{
		str = ft_strjoin_(str, arr[i++].command);
	}
	free(arr);
	return (str);
}

t_command	cooking(char *str, int p, int x, t_data *data)
{
	t_command	arr2;
	t_command	*arr;
	t_indexes	indx;

	arr = cleaning(str, p, NULL, indx);
	arr2.q = arr[0].q;
	arr->data = data;
	arr->envp = *(data->envp);
	if (!x)
		expand(arr, data);
	arr2.command = ft_arr_to_str(arr);
	free(str);
	return (arr2);
}
