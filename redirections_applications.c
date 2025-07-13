/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/13 09:44:08 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char ** apply_redirections(char **command, t_command *arr)
{
	int i = 0;
	int count = 0;
	char **cmd = clean_command(command, arr);
	// list(cmd);
	// exit(0);
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0 && arr[i].q == 0)
			redirect_output_fd(command);
		if (ft_strcmp(command[i], "<") == 0 && arr[i].q == 0)
			redirect_input_fd(command);
		if (ft_strcmp(command[i], ">>") == 0 && arr[i].q == 0)
			append_to_fd(command);
		i++;
	}
	return (cmd);
}