/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:19:57 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/04 19:03:33 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_data	*get_heredoc_data(t_data *new_data)
{
	static t_data	*stored_data = NULL;

	if (new_data != NULL)
		stored_data = new_data;
	return (stored_data);
}

void	bash_sig_handler(int signum)
{
	t_data	*data;
	int		p;

	(void)signum;
	data = get_heredoc_data(NULL);
	p = 0;
	while (p < data->id)
	{
		kill(data->pid[p++], SIGTERM);
	}
	data->status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_hsig == 0)
		rl_redisplay();
	g_hsig = 0;
}

void	signal_init(t_data *data)
{
	get_heredoc_data(data);
	g_hsig = 0;
	if (signal(SIGINT, bash_sig_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal failed");
		return ;
	}
}

void	signal_init_here(t_data *data)
{
	get_heredoc_data(data);
	if (signal(SIGINT, heredoc_sigint_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal failed");
		return ;
	}
}

void	heredoc_sigint_handler(int signum)
{
	t_data	*data;

	(void)signum;
	data = get_heredoc_data(NULL);
	if (data)
	{
		heredoc_child_cleanup(data->limiters, data->file, data->com);
		exit(130);
	}
}
