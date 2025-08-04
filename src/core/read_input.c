/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/04 19:01:06 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_hsig = 0;

int	check_command(char **str, char ***envp, t_node *node, t_data *data)
{
	if (!str || !*str)
		return (0);
	if (!(ft_strcmp(str[0], "echo")))
		return (echo(str, data, 0), 0);
	if (!(ft_strcmp(str[0], "cd")))
		return (cd(envp, &str[1], data), 0);
	if (!(ft_strcmp(str[0], "pwd")))
		return (pwd(data), 0);
	if (!(ft_strcmp(str[0], "minishell")))
		return (minishell(str, data), 0);
	if (!(ft_strcmp(str[0], "export")))
		return (export(envp, node->command, data), 0);
	if (!(ft_strcmp(str[0], "unset")))
		return (unset(envp, str, data), 0);
	if (!(ft_strcmp(str[0], "env")))
		return (print_env(*envp, node->command, data), 0);
	if (!(ft_strcmp(str[0], "exit")))
		return (ft_exit(envp, node, data), 0);
	return (1);
}

static void	init_loop_data(t_data *data)
{
	int	k;

	data->fd = -1;
	k = 0;
	while (k < 2000)
	{
		data->pid[k] = 0;
		k++;
	}
	data->id = 0;
}

static void	handle_null_command(char ***envp, t_data *data)
{
	ft_print("exit", 0);
	if (*envp)
		free_all_ul_split(*envp);
	if (data->path)
		free(data->path);
	if (data->pwd)
		free(data->pwd);
	if (data->pid)
		free(data->pid);
	cleanup_fds();
	exit(data->status);
}

static void	execute_command(t_node *node, char ***envp, t_data *data)
{
	t_node		*tmp;
	t_indexes	indx;

	tmp = node;
	if (node->next)
	{
		pip(envp, data, node);
		free_all_node(node);
		return ;
	}
	indx.i = dup(0);
	indx.j = dup(1);
	indx.p = 0;
	tmp->command = apply_redirections(tmp, envp, data, indx);
	if (tmp->command && check_command(tmp->command, envp, node, data))
	{
		exe(*envp, node, data);
		if (data->fd != -1)
			close(data->fd);
	}
	indx.p = 1;
	apply_redirections(tmp, envp, data, indx);
	free_all_node(node);
}

void	read_input(char ***envp, t_data *data)
{
	char	*command;
	t_node	*node;

	signal_init(data);
	while (1)
	{
		node = NULL;
		init_loop_data(data);
		command = readline(
				"\001\033[38;5;93m\002MINISHELL-1.0$ "
				"\001\033[0m\002");
		if (!command)
			handle_null_command(envp, data);
		add_history(command);
		if (command_analyze(command, data) == 0)
		{
			command_tokenization(&node, command, *envp, data);
			execute_command(node, envp, data);
		}
		free(command);
	}
}
