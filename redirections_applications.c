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
char **apply_redirections(char **command, t_command *arr, char **envp, t_data *data, int p)
{
	static int s_in = -1;
	static int s_out = -1;
	int i = 0;
	char **cmd;
	if (p == 0)
	{
		s_in = dup(0);
		s_out = dup(1);
		if (s_in == -1 || s_out == -1)
			return (NULL);
		while (command[i])
		{
			if (ft_strcmp(command[i], ">") == 0 && arr[i].q == 0)
			{
				if (redirect_output_fd(command, data) == -1)
					return (NULL);
			}
			else if (ft_strcmp(command[i], ">>") == 0 && arr[i].q == 0)
			{
				if (append_to_fd(command, data) == -1)
					return (NULL);
			}
			else if (ft_strcmp(command[i], "<") == 0 && arr[i].q == 0)
			{
				if (redirect_input_fd(command, data) == -1)
					return (NULL);
			}
			else if (ft_strcmp(command[i], "<<") == 0 && arr[i].q == 0)
			{
				here_doc(command, arr, envp, data);
			}
			i++;
		}
		cmd = clean_command(command, arr);
		free_all_ul_split(command);
		return (cmd);
	}
	if (s_in == -1 || s_out == -1)
		return (NULL);
	if (dup2(s_in, 0) == -1 || dup2(s_out, 1) == -1)
		return (NULL);
	close(s_in);
	close(s_out);
	s_in = -1;
	s_out = -1;
	return (NULL);
}
