/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/03 15:50:32 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(char **command)
{
	int i = 0;
	int count = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0)
			redirect_output_fd(command);
		if (ft_strcmp(command[i], "<") == 0)
			redirect_input_fd(command);
		i++;
	}

}