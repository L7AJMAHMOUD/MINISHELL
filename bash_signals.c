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


static t_data *get_heredoc_data(t_data *new_data)
{
    static t_data *stored_data = NULL;
    
    if (new_data != NULL)
        stored_data = new_data;
    
    return stored_data;
}

void signal_init_here(t_data *data)
{
    get_heredoc_data(data);
    
    if (signal(SIGINT, heredoc_sigint_handler) == SIG_ERR
        || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
        perror("signal failed");
        return;
    }
}

void heredoc_sigint_handler(int signum)
{
    t_data *data;
    
    (void)signum;
    write(1, "\n", 1);
    data = get_heredoc_data(NULL);
    if (data && data->path)
    {
		heredoc_child_cleanup(data->limiters, data->file, data->com);
		exit(130);
    }
}
