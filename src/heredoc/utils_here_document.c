#include "../../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	g;
	char	*str;

	j = 0;
	g = 1;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	g = ft_strlen(s) - start;
	if (g >= len)
		g = len;
	str = malloc(sizeof(char) * (g + 1));
	if (str == NULL)
		return (0);
	while (s[start] && j < len)
		str[j++] = s[start++];
	str[j] = '\0';
	return (str);
}

int	delimiters_counter(t_command *arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arr[i].command)
	{
		if (ft_strcmp(arr[i].command, "<<") == 0 && arr[i + 1].command
			&& arr[i].q == 0)
		{
			i += 2;
			count++;
		}
		else
			i++;
	}
	return (count);
}

char	**get_delimiters(t_command *arr, char **command)
{
	int		delim;
	char	**deli_stack;
	int		i;
	int		j;

	delim = delimiters_counter(arr);
	deli_stack = malloc((delim + 1) * sizeof(char *));
	i = 0;
	j = 0;
	if (!deli_stack)
		return (NULL);
	while (arr[i].command)
	{
		if (ft_strcmp(arr[i].command, "<<") == 0 && arr[i + 1].command
			&& arr[i].q == 0)
		{
			if (arr[i + 1].k != 0)
				deli_stack[j++] = ft_strdup(command[i++ + 1]);
			else
				deli_stack[j++] = ft_strdup(arr[i++ + 1].command);
		}
		else
			i++;
	}
	return (deli_stack[j] = NULL, deli_stack);
}

void	heredoc_child_cleanup(char **limiters, char *file, char *com)
{
	if (limiters)
		free_all_ul_split(limiters);
	if (file)
		free(file);
	if (com)
		free(com);
}
