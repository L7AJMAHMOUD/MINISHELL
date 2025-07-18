/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/16 12:46:56 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char ** apply_redirections(char **command, t_command *arr, char **envp, t_data *data)
{
	int i = 0;
	char **cmd = clean_command(command, arr);

	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0 && arr[i].q == 0)
			redirect_output_fd(command);
		if (ft_strcmp(command[i], "<") == 0 && arr[i].q == 0)
			redirect_input_fd(command);
		if (ft_strcmp(command[i], ">>") == 0 && arr[i].q == 0)
			append_to_fd(command);
		if (ft_strcmp(command[i], "<<") == 0 && arr[i].q == 0)
			here_doc(command, arr, envp, data);
		i++;
	}
	i  = 0;
	free_all_ul_split(command);
	return (cmd);
}
