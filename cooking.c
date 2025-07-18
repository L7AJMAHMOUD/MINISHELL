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

void free_(t_command *arr, int k)
{
	int m;

	m = 0;
	while (m < k)
		free(arr[m++].command);
	free(arr);
}

void malloc_(t_command *arr, char *str, int *k, int j)
{
	arr[*k].command[j] = 0;
	*k += 1;
	arr[*k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
}

t_command *cleaning(char *str, int p)
{
    t_command *arr;
    int i = 0;  
    int j = 0;  
    int k = 0;  
    int c;

	arr = malloc(sizeof(t_command) * (ft_strlen(str) + 1));
    if (!arr)
		return NULL;
	ft_memset(arr, 0, sizeof(t_command) * (ft_strlen(str) + 1));
    arr[k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!arr[k].command)
        return (free(arr), NULL);
    while (str[i])
	{
        if (str[i] == QUOTE_SINGLE || str[i] == QUOTE_DOUBLE)
        {
			if (j != 0)
				malloc_(arr, str, &k, j);
			j = 0;
            c = str[i++];
			if (c == str[i] && p == 0 && !str[i+1])
			{
				free(arr[k].command);
				arr[k].command = ft_strdup("''");
				j += 2;
				continue;
			}
			arr[k].q = c;
            while (str[i] && str[i] != c)
                arr[k].command[j++] = str[i++];
            if (str[i] == c)
                i++;
            arr[k++].command[j] = '\0';
            j = 0;
			if (!str[i])
			{
				arr[k].command = NULL;
				arr->nbr = k;
				return arr;
			}
            arr[k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
            if (!arr[k].command)
                return (free_(arr, k), NULL);
        }
        else
            arr[k].command[j++] = str[i++];
    }
    arr[k++].command[j] = '\0';
    arr[k].command = NULL;
    arr->nbr = k;
    return arr;
}

char *get_from_envp(char *str, char **envp)
{
	int b = 0;
	char *tmp;
	while(envp[b])
	{
		tmp = ft_shearch(str, envp[b++]);
		if (tmp)
			return(tmp);
	}
	return NULL;
}
int strlen_(char *str)
{
	int i;
	i = 0;
	if (!str)
		return 0;
	while (str[i] && str[i] != '$' && str[i] != QUOTE_SINGLE && str[i] != QUOTE_DOUBLE && str[i] != 32 && str[i] != '<' && str[i] != '>')
	{
		i++;
	}
	return i;
}

char* get_variable(char *str, char **envp)
{
    int i = 0;
    int len;
    char *equal_pos;
    
    if (!str || !envp)
        return NULL;
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
    return NULL;
}

void ul_expand(t_command *arr, int i, int *j, int p)
{
	int var_len;
	char *varname;
	char *val;
	char *tmp;
	char *str;

	var_len = strlen_(&(arr[i].command[*j]));
	varname = malloc(var_len + 1);
	if (!varname)
		return;
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
void ulr_expand(t_command *arr, int i, int *j, int p)
{
	int var_len;
	char *varname;
	char *val;
	char *tmp;
	char *str;

	var_len = 1;
	varname = malloc(var_len + 1);
	if (!varname)
		return;
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

void ultra_expand(t_command *arr, int i, int *p, int j)
{
	char *str;

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

void while_(t_command *arr, int *i, int *j, int *p)
{
	while (arr[*i].command[*j] == '$')
	{
		*j = *j + 1;
		*p = *p + 1;
	}
}

void	handle_dollar(t_command *arr, int i)
{
	int	j;
	int	p;
	int	m;

	j = 0;
	while (arr[i].command[j])
	{
		if (arr[i].command[j++] == '$')
		{
			p = 0;
			m = j;
			while_(arr, &i, &j, &p);
			if (!arr[i].command[j] && !arr[i + 1].command)
				continue;
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
			handle_dollar(arr, i);
		if (arr[i].command[0] == 0 && arr[i].q == 0)
		{
			free(arr[i].command);
			arr[i].command = NULL;
		}
		i++;
	}
}


char *ft_arr_to_str(t_command *arr)
{
	int i = 0;
	char *str;
	str = NULL;
	while (i < arr->nbr)
	{
		str = ft_strjoin_(str, arr[i++].command);
	}
	free(arr);
	return str;
}


t_command cooking(char *str, char **envp, int p, int x, t_data *data)
{
	t_command arr2;
	t_command *arr = cleaning(str, p);
	arr2.q = arr[0].q;
	arr->data = data;
	arr->envp = envp;
	if (!x)
		expand(arr);
	arr2.command = ft_arr_to_str(arr);
	free(str);
	return arr2;
}