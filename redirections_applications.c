/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/22 14:58:43 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(char **command)
{
	int i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
			redirect_output_fd(command);
		i++;
	}
	
}

// [ls] ----> [>] ----> [p]
// [>] ----> [p] ----> [ls]
// [ls] ----> [>] ----> [p] ----> [x]
// [>] ----> [ls] ----> [p]