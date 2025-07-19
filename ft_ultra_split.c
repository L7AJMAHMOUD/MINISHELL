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


void free_arr(t_command *arr, int i)
{
	while (i >= 0)
		free(arr[i--].command);
	free(arr);
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
void	preparation(char **s, int i)
{
	int c;
	char *tmp;

	while ((*s)[i])
	{
		if ((*s)[i] == QUOTE_SINGLE || (*s)[i] == QUOTE_DOUBLE)
		{
			c = (*s)[i++];
			while ((*s)[i] != c && (*s)[i])
				i++;
			i++;
			continue;
		}
		if ((*s)[i] == '<' || (*s)[i] == '>' || (*s)[i] == '|')
		{
			c = (*s)[i];
			while ((*s)[i] == c && (*s)[i])
				i++;
			tmp = ft_strdup(&(*s)[i]);
			(*s)[i++] = 0;
			*s = ft_strjoin(*s, tmp);
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


char **ft_arr_to_tab(t_command *arr, int words, int i, int j)
{
	char **tab;

	if (!arr || words <= 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	while (j < words)
	{
		if (!arr[j].command)
		{
			j++;
			continue;
		}
		tab[i] = ft_strdup(arr[j].command);
		if (!tab[i++])
			return(free_all_ul_split(tab), NULL);
		j++;
	}
	tab[i] = NULL;
	free_arr(arr, i);
	return (tab);
}


int complit_(t_command *arr, int words, int *j, char *tmp)
{
	int x;
	int i;
	int k;

	i = 0;
	while (*j < words)
	{
		x = 0;
		while(tmp[i] == 32)
			i++;
		arr[*j].command=malloc(sizeof(char) * ln(&tmp[i]) + 1);
		if (!arr[*j].command)
			return 	(free_arr(arr, *j), 1);
		k = i + ln(&tmp[i]);
		while (i < k)
			arr[*j].command[x++] = tmp[i++];
		arr[*j].command[x] = 0;
			*j += 1;
		i++;
	}
	return 0;
}

t_command *ft_ultr_split(char *str, char ** envp, int q, t_data *data)
{
	t_command *arr;
	int j;
	int words;
	char *tmp;

	j = 0;
	tmp = ft_strdup(str);
	preparation(&tmp, 0);
	rev_(tmp);
	preparation(&tmp, 0);
	rev_(tmp);
	words = count_words(tmp, ' ', 0, 0);
	arr = malloc(sizeof(t_command) * words);
	if (!arr)
		return (NULL);
	if (complit_(arr, words, &j, tmp))
		return NULL;
	j = 0;
	while(j < words)
	{
		arr[j] = cooking(arr[j].command, envp, j, q, data);
		j++;
	}
	free(tmp);
	return(arr->nbr = words, arr);
}

char	**ft_ultra_split(char *str ,char ** envp, t_data *data)
{
	t_command *arr = ft_ultr_split(str, envp, 0, data);
	char **tab = ft_arr_to_tab(arr, arr->nbr, 0, 0);
	return(tab);
}
