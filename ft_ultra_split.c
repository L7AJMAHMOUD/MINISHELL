#include "minishell.h" 

void rev_(char *s)
{
    int i;
    int j;
    int c;

    if (!s)
        return;

    i = 0;
    j = ft_strlen(s) - 1;

    while (i < j)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        i++;
        j--;
    }
}

void comp_(char *s, int *i, int *count)
{
	char quote;

	if (*i == 0 || s[*i - 1] == SPACE_CHAR || s[*i - 1] == ' ')
		*count = *count + 1;
	quote = s[*i];
	*i += 1;
	while ((s[*i] && s[*i] != quote && s[*i] != PIPE_CHAR))
		*i += 1;
	if (s[*i] == quote)
		*i += 1;
}

int count_words(char *s, char sep, int i, int count)
{
    if (!s)
        return 0;
    while (s[i] && s[i] != PIPE_CHAR)
    {
        while (s[i] == SPACE_CHAR)
            i++;
        if (!s[i] || s[i] == PIPE_CHAR)
            break;
		if (s[i] == QUOTE_SINGLE || s[i] == QUOTE_DOUBLE)
        	comp_(s, &i, &count);
        else if (s[i] != sep)
        {
			if (i == 0 || s[i - 1] == SPACE_CHAR || s[i - 1] == sep)
            	count++;
            while (s[i] && s[i] != sep && s[i] != QUOTE_SINGLE 
                   && s[i] != QUOTE_DOUBLE && s[i] != PIPE_CHAR)
                i++;
        }
        else
            i++;
    }
    return count;
}
void	preparation(char **s)
{
	int i;
	int c;
	char *tmp;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == QUOTE_SINGLE || (*s)[i] == QUOTE_DOUBLE)
		{
			c = (*s)[i];
			i++;
			while ((*s)[i] != c)
			{
				i++;
			}
			i++;
			continue;
		}
		if ((*s)[i] == '<' || (*s)[i] == '>' || (*s)[i] == '|')
		{
			c = (*s)[i];
			while ((*s)[i] == c && (*s)[i])
				i++;
			tmp = ft_strdup(&(*s)[i]);
			(*s)[i] = 0;
			*s = ft_strjoin(*s, tmp);
			i++;
			continue;
		}
		i++;
	}
}

int initialisation(t_command *arr, int word)
{
	int i;
	
	i = 0;
	while(i < word)
	{
		arr[i].command = NULL;
		i++; 
	}
	return 0;
}
static int	ln(char *s)
{
	int	length;
	char c;
	char x;

	c = ' ';
	length = 0;
	while (s[length] && s[length] != c && s[length] != '>' && s[length] != '<')
	{
		if (s[length] == QUOTE_SINGLE || s[length] == QUOTE_DOUBLE)
		{
			x = s[length];
			length++;
			while (s[length] != x && s[length])
			{
				length++;
			}
			length++;
			continue;
		}
		length++;
	}
	while (s[length] == '>' || s[length] == '<')
		length++;
	return (length);
}


char **ft_arr_to_tab(t_command *arr, int words)
{
	char **tab;
	int i;
	int j;

	if (!arr || words <= 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		if (!arr[j].command)
		{
			j++;
			continue;
		}
		tab[i] = ft_strdup(arr[j].command);
		if (!tab[i])
		{
			while (i--)
				free(tab[i]);
			free(tab);
			return (NULL);
		}
		i++;
		j++;
	}
	tab[i] = NULL;
	i = 0;
	while (i < words)
	{
		free(arr[i++].command);
	}
	free(arr);
	return (tab);
}


t_command *ft_ultr_split(char *str, int	i, int		j,char ** envp, int *words, int q, t_data *data)
{
	t_command *arr;
	int x;
	int k;
	char *tmp;
	tmp = ft_strdup(str);
	preparation(&tmp);
	rev_(tmp);
	preparation(&tmp);
	rev_(tmp);
	printf("%s\n",tmp);
	*words = count_words(tmp, ' ', 0, 0);
	arr = malloc(sizeof(t_command) * *words);
	i = 0;
	while (j < *words)
	{
		x = 0;
		while(tmp[i] == 32)
			i++;
		arr[j].command=malloc(sizeof(char) * ln(&tmp[i]) + 1);
		k = i + ln(&tmp[i]);
		while (i < k)
		{
			arr[j].command[x] = tmp[i];
			i++;
			x++;
		}
		arr[j].command[x] = 0;
		i++;
		j++;
	}
	for (int v = 0; v < *words; v++)
	{
		arr[v] = cooking(arr[v].command, envp, v, q, data);
	}
	free(tmp);
	return(arr);
}

char	**ft_ultra_split(char *str, int	i, int		j,char ** envp, t_data *data)
{
	int words;
	t_command *arr = ft_ultr_split(str, i, j,envp, &words, 0, data);
	char **tab = ft_arr_to_tab(arr, words);
	return(tab);
}
