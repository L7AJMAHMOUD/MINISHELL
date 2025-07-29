/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:19:57 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/24 21:11:11 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void bash_sig_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
    rl_replace_line("", 0);
	if (g_hsig == 0)
    	rl_redisplay();
}

void heredoc_sigint_handler(int signum)
{
	exit(130);
}

void signal_init(t_data *data)
{
	if (signal(SIGINT, bash_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal failed");
		return;
	}
	int i = 0;
	while (i < data->id)
		kill(data->pid[i++], SIGKILL);
}

void signal_init_here(t_data *data)
{
	if (signal(SIGINT, heredoc_sigint_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal failed");
		return;
	}
}
