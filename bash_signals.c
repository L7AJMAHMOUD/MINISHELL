/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:19:57 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/17 09:46:32 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_init()
{
    if (signal(SIGINT, bash_sig_handler) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
        perror("signal failed");
        return ;
    }
}

void    bash_sig_handler(int sig)
{
    (void)sig;
    write(1, "\n", 2);
    if (rl_on_new_line() == -1)
        return ;
    rl_replace_line("", 0);
    rl_redisplay();  
    return ;
}

