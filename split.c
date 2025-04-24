#include "minishell.h"

static char	**free_alocation(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	ln(char *s, char c)
{
	int	length;

	length = 0;
	while (s[length] && s[length] != c)
		length++;
	return (length);
}

static char	**double_array(int words)
{
	char	**p;

	p = malloc((words + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	return (p);
}

static int	count_word(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		len_w;
	char	**k;

	if (!s)
		return (NULL);
	words = count_word((char *)s, c);
	i = -1;
	k = double_array(words);
	if (!k)
		return (NULL);
	while (++i < words)
	{
		while (*s == c)
			s++;
		len_w = ln((char *)s, c);
		k[i] = malloc((len_w + 1) * sizeof(char));
		if (!k[i])
			return (free_alocation(k));
		ft_strlcpy(k[i], s, len_w + 1);
		k[i][len_w] = '\0';
		s = s + len_w;
	}
	return (k[i] = NULL, k);
}