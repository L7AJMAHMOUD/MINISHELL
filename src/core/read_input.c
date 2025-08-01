/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/30 12:02:55 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_hsig = 0;

void free_all_node(t_node *node)
{
	t_node *tmp;
	while (node)
	{
		tmp = node->next;
		free_all_ul_split(node->command);
        free_arr(node->arr, node->i - 1);
		free(node);
		node = tmp;
	}
}

void print_env(char **envp, char **command, t_data *data)
{
    int i;

    i = 0;
    if (command[1])
    {
        ft_print("my shell must implement env with no options or arguments ​.​", 0);
        data->status = 125;
        return;
    }
    else
        while (envp && envp[i])
            printf("%s\n", envp[i++]);
    data->status = 0;
    
}
void minishell(char **str, t_data *data)
{
	data->status = 0;
    if (!str[1])
        printf("\ntry : ./minishell \n\033[7mEvery command has consequences...\033[0m\n\n");
    else if (!(ft_strcmp(str[1], "--version")) && !str[2])
    printf("\nMINISHELL, version 1.0.0 (x64-pc-linux-gnu)\n"
            "Copyright (C) 2025 Free Software Foundation, Inc.\n\n"
            "This is free software: you are free to modify and redistribute it\n"
            "under the terms of the GNU General Public License.\n"
            "There is NO WARRANTY, to the extent permitted by law.\n\n"
            "Developed by:\n"
            "  Abderrahman Karam      (abkaram) / " " Mahmoud En-Najy       (maen-naj)\n\n"
            "Forged in sleepless nights ☕, driven by pure logic 🧠,\n"
            "and crafted with heart ❤, byte by byte.\n"
            "Inspired by the soul of /bin/bash and the ghosts of UNIX past 👻.\n"
            "Every line of code written under the watchful eye of Norminette 😤.\n");
    else
	{
		data->status = 2;
        ft_print("minishell : invalid option\nminishell options:\n\t--version",0);
	}
}

int	ft_strisdigit(char *c)
{
	int i = 0;

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
		data->status = 1;
		return ;
	}
	if (node->command[1])
	{
		if (ft_strisdigit(node->command[1]))
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


int check_command(char **str, char ***envp, t_node *node, t_data *data)
{
    if (!str || !*str)
		return 0;
    if (!(ft_strcmp(str[0], "echo")))
        return (echo(str, data), 0);
    if (!(ft_strcmp(str[0], "cd")))
        return (cd(envp, &str[1], data), 0);
    if (!(ft_strcmp(str[0], "pwd")))
        return (pwd(data), 0);
    if (!(ft_strcmp(str[0], "minishell")))
        return (minishell(str, data), 0);
    if (!(ft_strcmp(str[0], "export")))
        return (export(envp, node->command, data), 0);
    if (!(ft_strcmp(str[0], "unset")))
        return (unset(envp, str, data) ,0);
    if (!(ft_strcmp(str[0], "env")))
        return (print_env(*envp, node->command, data), 0);
    if (!(ft_strcmp(str[0], "exit")))
        return (ft_exit(envp, node, data), 0);
    return (1);
}
int check_node_syntex(t_node *tmp)
{
    while(tmp)
    {
        if ((!(ft_strcmp((tmp)->command[0], ">")) || !(ft_strcmp((tmp)->command[0], "<"))
            || !(ft_strcmp((tmp)->command[0], "<<")) || !(ft_strcmp((tmp)->command[0], "<<")))
                && !tmp->command[1])
        {
            ft_print("minishell: syntax error near unexpected token `nightmare' 😉.​", 0);
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

int wait_for_child(pid_t pid, t_data *data)
{
	int status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	waitpid(pid, &status, 0);

	signal_init(data);
	return status;
}

static void	init_loop_data(t_data *data)
{
	data->fd = -1;
	for (int k = 0; k < 2000; k++)
		data->pid[k] = 0;
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
	t_node	*tmp;
	t_indexes	indx;

	tmp = node;
	if (node->next)
	{
		pip(envp, data, node);
		free_all_node(node);
		return ;
	}
	indx.i = -1;
	indx.j = -1;
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
		command = readline("\001\033[38;5;93m\002MINISHELL-1.0$ \001\033[0m\002");
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


