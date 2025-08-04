#include "../../minishell.h"

void	reset_node_flags(t_node *node)
{
	node->command = 0;
	node->pipe = 0;
	node->next = 0;
}
