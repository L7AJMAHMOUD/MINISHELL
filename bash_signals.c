/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:19:57 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/30 11:50:26 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void bash_sig_handler(int signum)
{
	(void)signum;

	write(1, "\n", 1);	
	g_hsig = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

}

void signal_init(t_data * data)
{
	if (signal(SIGINT, bash_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal failed");
		return;
	}
}


void heredoc_sigint_handler(int signum)
{
	(void)signum;
	write(1,"\n", 1);
	exit(130);
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
