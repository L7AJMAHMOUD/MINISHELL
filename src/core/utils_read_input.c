/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:25:54 by abkaram           #+#    #+#             */
/*   Updated: 2025/08/04 22:30:16 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_all_node(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free_all_ul_split(node->command);
		free_arr(node->arr, node->i - 1);
		free(node);
		node = tmp;
	}
}

void	print_env(char **envp, char **command, t_data *data)
{
	int	i;

	i = 0;
	if (command[1])
	{
		ft_print("my shell must implement env with no arguments ​.​", 0);
		data->status = 125;
		return ;
	}
	else
		while (envp && envp[i])
			printf("%s\n", envp[i++]);
	data->status = 0;
}

void	minishell(char **str, t_data *data)
{
	data->status = 0;
	if (!str[1])
		printf("\ntry : ./minishell \n\n");
	else if (!(ft_strcmp(str[1], "--version")) && !str[2])
		printf("\nMINISHELL, version 1.0.0 (x64-pc-linux-gnu)\n"
			"Copyright (C) 2025 Free Software Foundation, Inc.\n\n"
			"free software: you are free to modify and redistribute it\n"
			"under the terms of the GNU General Public License.\n"
			"There is NO WARRANTY, to the extent permitted by law.\n\n"
			"Developed by:\n"
			"  Abderrahman Karam (abkaram) / " " Mahmoud En-Najy (maen-naj)\n\n"
			"Forged in sleepless nights ☕, driven by pure logic 🧠,\n"
			"and crafted with heart ❤, byte by byte.\n");
	else
	{
		data->status = 2;
		ft_print("minishell: invalid option\n", 0);
		ft_print("minishell options:\n\t--version", 0);
	}
}

int	ft(char *c)
{
	int	i;

	i = 0;
	while (c[i] <= 32)
		i++;
	if (!c || c[i] == '\0')
		return (0);
	if (c[i] == '-' || c[i] == '+')
		i++;
	if (c[i] == '\0')
		return (0);
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (0);
		i++;
		if (c[i] <= 32)
		{
			while (c[i] <= 32 && c[i])
				i++;
			if (c[i])
				return (0);
		}
	}
	return (1);
}

void	ft_exit(char ***envp, t_node *node, t_data *data)
{
	printf("exit\n");
	if (node->command[1] && node->command[2])
	{
		ft_print("exit: too many arguments", 0);
		data->status = 2;
		return ;
	}
	if (node->command[1])
	{
		if (ft(node->command[1]) && (ft_atoi(node->command[1]) != -1))
			data->status = ft_atoi(node->command[1]) % 256;
		else
		{
			ft_print("exit: numeric argument required", 0);
			data->status = 2;
			return ;
		}
	}
	free_all_ul_split(*envp);
	free_all_node(node);
	free(data->path);
	free(data->pwd);
	free(data->pid);
	cleanup_fds();
	exit(data->status);
}
