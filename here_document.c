/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:49:37 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/17 05:43:20 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	here_doc(char **command, t_command *arr, char **envp, t_data *data)
{
	(void)arr;
	(void)envp;
	(void)data;
	list(command);
}