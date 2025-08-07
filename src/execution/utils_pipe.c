/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:15:29 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:15:30 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
