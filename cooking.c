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

t_command *cleaning(char *str, int p)
{
    int i = 0;  
    int j = 0;  
    int k = 0;  
    int m = 0;  
    int c;      
    int len = ft_strlen(str);

    t_command *arr = malloc(sizeof(t_command) * (len + 1));
    if (!arr) return NULL;

    arr[k].command = malloc(sizeof(char) * (len + 1));
    if (!arr[k].command) {
        free(arr);
        return NULL;
    }

    while (str[i]) {
        if (str[i] == QUOTE_SINGLE || str[i] == QUOTE_DOUBLE)
        {
			if (j != 0)
			{
				arr[k].command[j] = 0;
				k++;
				arr[k].command = malloc(sizeof(char) * (len + 1));
			}
			j = 0;
            c = str[i++];
			if (c == str[i] && k == 0 && p == 0 && !str[i+1])
			{
				free(arr[k].command);
				arr[k].command = ft_strdup("''");
				j += 2;
				continue;
			}
			// if (c == str[i] && k == 0 && p != 0 && !str[i+1])
			// {
			// 	free(arr[k].command);
			// 	arr[k].command = malloc(2);
			// 	arr[k].command[0] = 2;
			// 	arr[k].command[1] = 0;
			// 	j += 2;
			// 	continue;
			// }
			arr[k].q = c;
            while (str[i] && str[i] != c) {
                arr[k].command[j++] = str[i++];
            }
            if (str[i] == c)
                i++;
            arr[k].command[j] = '\0';
            j = 0;
            k++;
			if (!str[i])
			{
				arr[k].command = NULL;
				arr->nbr = k;
				return arr;
			}
            arr[k].command = malloc(sizeof(char) * (len + 1));
            if (!arr[k].command) {
                while (m < k)
                    free(arr[m++].command);
                free(arr);
                return NULL;
            }
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
	while (str[i] && str[i] != '$' && str[i] != QUOTE_SINGLE && str[i] != QUOTE_DOUBLE)
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

void	expand(t_command *arr, char **envp)
{
	char *str;
	char *tmp;
	char *varname;
	char *val;
	int i;
	int j;
	int var_len;
	int p;
	int m;
	i = 0;
	j = 0;
	while(i < arr->nbr)
	{
		j = 0;
		m = 0;
		if (arr[i].q == 39)
		{
			i++;
			continue;
		}
		while(arr[i].command[j])
		{
			if(arr[i].command[j++] == '$' && (arr[i].command[j] != QUOTE_SINGLE && arr[i].command[j] != QUOTE_DOUBLE))
			{
				p = 0;
				m = j;
				while (arr[i].command[j] == '$')
				{
					j++;
					p++;
				}
				if (!arr[i].command[j])
					continue;
				if (arr[i].q == 39 || p % 2 || (arr[i].command[j] >= '0' && arr[i].command[j] <= '9'))
				{
					if (arr[i].command[j] >= '0' && arr[i].command[j] <= '9')
						str = ft_strdup(&(arr[i].command[j + 1]));
					else
						str = ft_strdup(&(arr[i].command[j]));
					arr[i].command[j - ++p] = 0;
					arr[i].command = ft_strjoin_(arr[i].command, str);
					j = m;
				}
				else
				{	
					var_len = strlen_(&(arr[i].command[j]));
					varname = malloc(var_len + 1);
					if (!varname)
					return;
					strncpy(varname, &(arr[i].command[j]), var_len);
					varname[var_len] = '\0';
					tmp = get_variable(varname, envp);
					if (tmp)
						val = ft_strdup(tmp);
					else
						val = NULL;
					str = ft_strdup(&(arr[i].command[j + var_len]));
					arr[i].command[j - p - 1] = 0;
					arr[i].command = ft_strjoin_(arr[i].command,val);
					arr[i].command = ft_strjoin_(arr[i].command, str);
					j = --m;
				}
			}
		}
		if (arr[i].command[0] == 0 && arr[i].q == 0)
		{
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
		if (!arr[i].command)
		{
			i++;
			continue;
		}
		str = ft_strjoin_(str, arr[i++].command);
	}
	free(arr);
	return str;
}


char *cooking(char *str, char **envp, int p)
{
	t_command *arr = cleaning(str, p);
	expand(arr, envp);
	char *string = ft_arr_to_str(arr);
	free(str);
	return string;
}
