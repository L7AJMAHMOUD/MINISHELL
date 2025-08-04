#include "../../minishell.h"

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
