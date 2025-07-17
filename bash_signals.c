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

void    bash_sig_handler(int sig)
{
    write(1, "\n", 2);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();  
}