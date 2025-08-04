/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:46:35 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/04 19:02:49 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	invalid_param(void)
{
	write(2, "          🚨 INVALID MINISHELL PARAMETERS 🚨\n", 49);
	write(2, "\n", 1);
	write(2, "                    🚨  HELP  🚨\n", 37);
	write(2, "\n", 1);
	write(2, "       🚨 TRY RUNNING JUST THE EXECUTABLE FILE 🚨\n", 55);
	write(2, "\n", 1);
	write (2, "                   $ ./minishell\n", 33);
	write(2, "\n", 1);
	exit(1);
}
