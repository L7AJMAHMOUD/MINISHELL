/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/17 16:38:54 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_node *node_cmd)
{
	int i = 0;
	while (node_cmd)
	{
		while (node_cmd -> command[i])
		{
			if (ft_strcmp(node_cmd -> command[i], ">") == 0)
				printf("redirect_output_fd func\n");
			else if (ft_strcmp(node_cmd -> command[i], ">") == 0)
				printf("redirect_input_fd func\n");
			else if (ft_strcmp(node_cmd -> command[i], ">>") == 0)
				printf("fd_adder func\n");
			else if (ft_strcmp(node_cmd -> command[i], "<<")  == 0)
				printf("here_doc func\n");
			i++;
		}
		node_cmd = node_cmd -> next;
	}
}
