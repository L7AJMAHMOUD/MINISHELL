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
	return (free(s1), free(s2), str);
}

void	free_(t_command *arr, int k)
{
	int	m;

	m = 0;
	while (m < k)
		free(arr[m++].command);
	free(arr);
}

int	malloc_(t_command *arr, char *str, int *k, int j)
{
	arr[*k].command[j] = 0;
	*k += 1;
	arr[*k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[*k].command)
		return (free_arr(arr, *k - 1), 1);
	return (0);
}

int	complt_(t_command *arr, char *str, t_indexes *ind)
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
		return (free_(arr, ind->k), 1);
	return (0);
}

int	compl_(t_command *arr, t_indexes *indx, char *str)
{
	free(arr[indx->k].command);
	arr[indx->k].command = ft_strdup("''");
	if (!arr[indx->k].command)
		return (free_arr(arr, indx->k - 1), 1);
	indx->j = 0;
	indx->k++;
	arr[indx->k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[indx->k].command)
		return (free_(arr, indx->k), 1);
	return (0);
}

int	com_(t_command **arr, t_indexes *indx, char *str)
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
		return (free(arr), 1);
	return (0);
}

t_command	*return_(t_command *arr, int i)
{
	if (i == 1)
		return (NULL);
	return (arr);
}

int	check_(t_indexes *indx, char *str)
{
	indx->j = 0;
	indx->c = str[indx->i++];
	return (0);
}

t_command	*cleaning(char *str, int p, t_command *arr, t_indexes indx)
{
	if (com_(&arr, &indx, str))
		return (NULL);
	while (str[indx.i])
	{
		if (str[indx.i] == QUOTE_SINGLE || str[indx.i] == QUOTE_DOUBLE)
		{
			if (indx.j != 0)
				if (malloc_(arr, str, &(indx.k), indx.j))
					return (NULL);
			check_(&indx, str);
			if (indx.c == str[indx.i] && p == 0 && !str[indx.i + 1])
			{
				if (compl_(arr, &indx, str))
					return (NULL);
				continue ;
			}
			indx.c = complt_(arr, str, &indx);
			if (indx.c == 1 || indx.c == 2)
				return (return_(arr, indx.c));
		}
		else
			arr[indx.k].command[indx.j++] = str[indx.i++];
	}
	arr[indx.k].command[indx.j] = '\0';
	return (arr[++indx.k].command = NULL, arr->nbr = indx.k, arr);
}

int	strlen_(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '$' && str[i] != QUOTE_SINGLE
		&& str[i] != QUOTE_DOUBLE && str[i] != 32 && str[i] != '<'
		&& str[i] != '>')
	{
		i++;
	}
	return (i);
}

char	*get_variable(char *str, char **envp)
{
	int		i;
	int		len;
	char	*equal_pos;

	i = 0;
	if (!str || !envp)
		return (NULL);
	len = strlen_(str);
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
	return (NULL);
}

void	ul_expand(t_command *arr, int i, int *j, int p)
{
	int		var_len;
	char	*varname;
	char	*val;
	char	*tmp;
	char	*str;

	var_len = strlen_(&(arr[i].command[*j]));
	varname = malloc(var_len + 1);
	if (!varname)
		return ;
	strncpy(varname, &(arr[i].command[*j]), var_len);
	varname[var_len] = '\0';
	tmp = get_variable(varname, arr->envp);
	if (tmp)
		val = ft_strdup(tmp);
	else
		val = NULL;
	str = ft_strdup(&(arr[i].command[*j + var_len]));
	arr[i].command[*j - 1 - p] = 0;
	arr[i].command = ft_strjoin_(arr[i].command, val);
	var_len = ft_strlen(arr[i].command);
	arr[i].command = ft_strjoin_(arr[i].command, str);
	free(varname);
	*j = var_len;
}

void	ulr_expand(t_command *arr, int i, int *j, int p)
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

void	ultra_expand(t_command *arr, int i, int *p, int j)
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

void	while_(t_command *arr, int *i, int *j, int *p)
{
	while (arr[*i].command[*j] == '$')
	{
		*j = *j + 1;
		*p = *p + 1;
	}
}

void	handle_dollar(t_command *arr, int i, int j)
{
	int	p;
	int	m;

	while (arr[i].command[j])
	{
		if (arr[i].command[j++] == '$')
		{
			p = 0;
			m = j;
			while_(arr, &i, &j, &p);
			if (!arr[i].command[j] && !arr[i + 1].command)
				continue ;
			if (arr[i].q == 39 || p % 2
				|| (arr[i].command[j] >= '0' && arr[i].command[j] <= '9'))
			{
				ultra_expand(arr, i, &p, j);
				j = m;
			}
			else if (arr[i].command[j] == '?')
				ulr_expand(arr, i, &j, p);
			else
				ul_expand(arr, i, &j, p);
		}
	}
}

void	expand(t_command *arr)
{
	int	i;

	i = 0;
	while (i < arr->nbr)
	{
		if (arr[i].q != 39)
			handle_dollar(arr, i, 0);
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

t_command	cooking(char *str, char **envp, int p, int x, t_data *data)
{
	t_command	arr2;
	t_command	*arr;
	t_indexes	indx;

	arr = cleaning(str, p, NULL, indx);
	arr2.q = arr[0].q;
	arr->data = data;
	arr->envp = envp;
	if (!x)
		expand(arr);
	arr2.command = ft_arr_to_str(arr);
	free(str);
	return (arr2);
}
