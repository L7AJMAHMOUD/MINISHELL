#include "minishell.h"

static int	ft_an(char *haystack, char *needle)
{
	size_t	i;

	i = 0;
	while (haystack[i] == needle[i] && haystack[i])
		i++;
	if (i == ft_strlen(needle))
		return (1);
	return (0);
}

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == 0)
		return (haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[j])
			if (ft_an(&haystack[i], needle) == 1)
				return (&haystack[i + 2]);
		i++;
	}
	return (0);
}