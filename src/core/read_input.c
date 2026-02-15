/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:27:21 by abkaram          ###   ########.fr       */
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
	write_history(".minishell_history");
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
	int			s_in;
	int			s_out;

	tmp = node;
	if (node->next)
	{
		pip(envp, data, node);
		free_all_node(node);
		return ;
	}
	s_in = dup(STDIN_FILENO);
	s_out = dup(STDOUT_FILENO);
	indx.i = s_in;
	indx.j = s_out;
	tmp->command = apply_redirections(tmp, envp, data, indx);
	if (tmp->command && check_command(tmp->command, envp, node, data))
	{
		exe(*envp, node, data);
		if (data->fd != -1)
			close(data->fd);
	}
	dup2(s_in, STDIN_FILENO);
	dup2(s_out, STDOUT_FILENO);
	close(s_in);
	close(s_out);
	free_all_node(node);
}

void	read_input(char ***envp, t_data *data)
{
	char	*command;
	t_node	*node;

	signal_init(data);
	while (1)
	{
		cleanup_fds();
		node = NULL;
		init_loop_data(data);
		command = readline(
				"\001\033[38;5;93m\002MINISHELL-1.0$ "
				"\001\033[0m\002");
		if (!command)
			handle_null_command(envp, data);
		if (command_analyze(command, data) == 0)
		{
			add_history(command);
			command_tokenization(&node, command, *envp, data);
			execute_command(node, envp, data);
		}
		free(command);
	}
}
