/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/24 21:51:41 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**apply_redirections(t_node *node, char **envp, t_data *data, int p)
{
	static int s_in;
	static int s_out;
	int i;
	char **cmd;

	i = 0;
	s_in = -1;
	s_out = -1;
	if (p == 0)
	{

		s_in = dup(0);
		s_out = dup(1);
		if (s_in == -1 || s_out == -1)
			return (NULL);
		while (node->command[i])
		{
			data->i = 0;
			if (ft_strcmp(node->command[i], ">") == 0 && node->arr[i].q == 0)
			{
				if (redirect_output_fd(node->command, data) == -1)
					return (NULL);
			}
			else if (ft_strcmp(node->command[i], ">>") == 0 && node->arr[i].q == 0)
			{
				if (append_to_fd(node->command, data) == -1)
					return (NULL);
			}
			else if (ft_strcmp(node->command[i], "<") == 0 && node->arr[i].q == 0)
			{
				if (redirect_input_fd(node->command, data) == -1)
					return (NULL);
			}
			else if (ft_strcmp(node->command[i], "<<") == 0 && node->arr[i].q == 0)
			{
				if (here_doc(node, envp, data)  == -1 && node->arr[i].q == 0)
					return (NULL);
				i += (data->i) * 2;
				continue;
			}
			i++;
		}
		cmd = clean_command(node->command, node->arr);
		if (!cmd)
			return (NULL);
		// if (cmd)
		// 	free_all_ul_split(command);
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
