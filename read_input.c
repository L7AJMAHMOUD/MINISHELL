/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/16 23:29:50 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        ft_print("my shell must implement env with no options or arguments ​😉​", 0);
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
    printf("\nMINISHELL OF NIGHTMARES, version 1.0.0-release (x64-pc-linux-gnu)\n"
        "Copyright (C) 2025 Free Software Foundation, Inc.\n\n"
        "This is free software; you are free to change and redistribute it.\n"
        "There is NO WARRANTY, to the extent permitted by law.\n\n"
        "Developers:\n"
        "  Mahmoud En-Najy      --> maen-naj\n"
        "  Abderrahman karam    --> abkaram\n\n");
    else
	{
		data->status = 2;
        ft_print("minishell : invalid option\nminishell options:\n\t--version",0);
	}
}

int	ft_strisdigit(char *c)
{
	int i = 0;

	if (!c || c[0] == '\0')
		return (0);
	if (c[0] == '-' || c[0] == '+')
		i++;
	if (c[i] == '\0')
		return (0);
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (0);
		i++;
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
		}
	}
	free_all_ul_split(*envp);
	free_all_node(node);
	free(data->path);
	free(data->pwd);
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
void    read_input(char ***envp, t_data *data)
{
    char *command;
	t_node *node;
	t_node *tmp;

    while (1)
    {
        node = NULL;
        signal(SIGINT, bash_sig_handler);
        signal(SIGQUIT, SIG_IGN);
		data->fd = -1;
        if (data->status == 0)
            command = readline("\033[31m▄\033[32m︻\033[33mデ\033[34m══━\033[31m一\033[32m 🎯 > \033[0m" );
        else
            command = readline("\033[31m▄\033[32m︻\033[33mデ\033[34m══━\033[31m一\033[32m 💀 > \033[0m" );
        if (!command)
        {
            ft_print("\nexit", 0);
            free_all_ul_split(*envp);
            free(data->path);
            free(data->pwd);
            exit (data->status);
        }
        if (ft_strcmp(command,"I LOVE YOU") == 0)
        {
            shy_emoji_banner();
            continue;
        }
        add_history(command);
        if(command_analyze(command) == 0)
		{
            command_tokenization(&node, command, *envp, data);
	        tmp = node;
			if (node -> next)
			{
				pip(node, envp, data);
                free(command);
                command = NULL;
				continue;
			}
            tmp->command = apply_redirections(tmp->command, tmp->arr, *envp, data, 0);
	        if((tmp)->command && check_command((tmp)->command, envp, node, data))
            {
                exe(*envp, node, data);
            }
            apply_redirections(tmp->command, tmp->arr, *envp, data, 1);
	        free_all_node(node);
		}
        else if (command_analyze(command) == -1)
        {
            ft_print("minishell: syntax error near unexpected token `nightmare' 😉.​", 0);
            data->status = 2;
        }
        free(command);
        command = NULL;
    }
}
