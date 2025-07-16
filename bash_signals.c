/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:19:57 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/15 22:47:31 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bash_sig_handler(int sig)
{
    // write(1, "\n", 2);
    // rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();   
    write(1, "\n", 1);
    rl_on_new_line();
    rl_point = 0;
    rl_end = 0;
    rl_redisplay();
}