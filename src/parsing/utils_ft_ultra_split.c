#include "../../minishell.h"

void	rev_(char *s)
{
	int	i;
	int	j;
	int	c;

	if (!s)
		return ;
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

void	free_arr(t_command *arr, int i)
{
	if (!arr)
		return ;
	while (i >= 0)
	{
		free(arr[i].command);
		arr[i].command = NULL;
		i--;
	}
	free(arr);
}

void	comp_(char *s, int *i, int *count)
{
	char	quote;

	if (*i == 0 || s[*i - 1] == SPACE_CHAR || s[*i - 1] == ' ')
		*count = *count + 1;
	quote = s[*i];
	*i += 1;
	while ((s[*i] && s[*i] != quote && s[*i] != PIPE_CHAR))
		*i += 1;
	if (s[*i] == quote)
		*i += 1;
}

int	count_words(char *s, char sep, int i, int count)
{
	if (!s)
		return (0);
	while (s[i] && s[i] != PIPE_CHAR)
	{
		while (s[i] == SPACE_CHAR)
			i++;
		if (!s[i] || s[i] == PIPE_CHAR)
			break ;
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
	return (count);
}

void	preparation(char **s, int i)
{
	int		c;
	char	*tmp;

	while ((*s)[i])
	{
		if ((*s)[i] == QUOTE_SINGLE || (*s)[i] == QUOTE_DOUBLE)
		{
			c = (*s)[i++];
			while ((*s)[i] != c && (*s)[i])
				i++;
			i++;
			continue ;
		}
		if ((*s)[i] == '<' || (*s)[i] == '>' || (*s)[i] == '|')
		{
			c = (*s)[i];
			while ((*s)[i] == c && (*s)[i])
				i++;
			tmp = ft_strdup(&(*s)[i]);
			(*s)[i++] = 0;
			*s = ft_strjoin(*s, tmp);
			continue ;
		}
		i++;
	}
}
