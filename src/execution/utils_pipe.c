#include "../../minishell.h"

void	init_fds(int *fds)
{
	fds[0] = -1;
	fds[4] = dup(0);
	fds[5] = dup(1);
}

void	wait_and_update_status(t_data *data)
{
	while (1)
		if (wait(NULL) <= 0)
			break ;
	if (data->status % 2 == 0 && data->status != 0)
		data->status = data->status / 256;
}
