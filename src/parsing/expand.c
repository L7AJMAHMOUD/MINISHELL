#include "minishell.h"

static int	count_dollars(const char *s, int j)
{
	int	p = 0;

	while (s[j] == '$')
	{
		j++;
		p++;
	}
	return (p);
}

static int	handle_numeric_dollar(char **cmd, int *j, int p)
{
	char	*str;

	if ((*cmd)[*j] >= '0' && (*cmd)[*j] <= '9')
		str = ft_strdup(&(*cmd)[*j + 1]);
	else
		str = ft_strdup(&(*cmd)[*j]);
	if ((*cmd)[*j - (p + 1)] == '$')
		(*cmd)[*j - ++p] = 0;
	else
		(*cmd)[*j - p] = 0;
	*cmd = ft_strjoin_(*cmd, str);
	*j -= p;
	return (1);
}

static int	handle_exit_code(char **cmd, int *j, int p, t_data *data)
{
	char	*varname;
	char	*val;
	char	*str;

	varname = malloc(2);
	if (!varname)
		return (0);
	varname[0] = (*cmd)[*j];
	varname[1] = '\0';
	val = ft_itoa(data->status);
	str = ft_strdup(&(*cmd)[*j + 1]);
	(*cmd)[*j - 1 - p] = 0;
	*cmd = ft_strjoin_(*cmd, val);
	*j = ft_strlen(*cmd);
	*cmd = ft_strjoin_(*cmd, str);
	free(varname);
	return (1);
}

static int	handle_env_var(char **cmd, int *j, int p, t_data *data)
{
	char	*varname;
	char	*tmp;
	char	*val;
	char	*str;
	int		var_len;

	var_len = strlen_(&(*cmd)[*j]);
	varname = malloc(var_len + 1);
	if (!varname)
		return (0);
	ft_strncpy(varname, &(*cmd)[*j], var_len);
	varname[var_len] = '\0';
	tmp = get_variable(varname, *(data->envp), data);
	val = tmp ? ft_strdup(tmp) : NULL;
	str = ft_strdup(&(*cmd)[*j + var_len]);
	(*cmd)[*j - 1 - p] = 0;
	*cmd = ft_strjoin_(*cmd, val);
	*j = ft_strlen(*cmd);
	*cmd = ft_strjoin_(*cmd, str);
	free(varname);
	return (1);
}

char	*expand_str(char *cmd, char **envp, t_data *data)
{
    t_indexes indx;

	indx.j = 0;
	cmd = ft_strdup(cmd);
    *(data->envp) = envp;
	while (cmd[indx.j])
	{
		if (cmd[indx.j++] == '$')
		{
			indx.p = 0;
			indx.m = indx.j;
			indx.p = count_dollars(cmd, indx.j);
			indx.j += indx.p;
			if (!cmd[indx.j] && !cmd)
				continue;
			if (indx.p % 2 || (cmd[indx.j] >= '0' && cmd[indx.j] <= '9'))
				handle_numeric_dollar(&cmd, &indx.j, indx.p);
			else if (cmd[indx.j] == '?')
				handle_exit_code(&cmd, &indx.j, indx.p, data);
			else
				handle_env_var(&cmd, &indx.j, indx.p, data);
		}
	}
	if (cmd[0] == 0)
		return (free(cmd), NULL);
	return (cmd);
}
