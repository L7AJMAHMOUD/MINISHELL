#include "../../minishell.h"

void	reset_node_flags(t_node *node)
{
	node->command = 0;
	node->pipe = 0;
	node->next = 0;
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && i < n - 1)
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}
