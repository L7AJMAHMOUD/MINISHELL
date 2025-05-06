/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/06 11:47:32 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_all_node(t_node *node)
{
    while (node)
    {
        free_all_ul_split(node->command);
        free(node);
        node = node->next;
    }
    
}

void export(char **envp, char **command)
{
    
}

int check_command(char **str, char **envp, t_node *node)
{
    if (!(ft_strcmp(str[0], "echo")))
        return (echo(str, 1), 0);
    if (!(ft_strcmp(str[0], "cd")))
        return (0);
    if (!(ft_strcmp(str[0], "pwd")))
        return (pwd(envp), 0);
    if (!(ft_strcmp(str[0], "export")))
        return (export(envp, node->command), 0);
    if (!(ft_strcmp(str[0], "unset")))
        return (0);
    if (!(ft_strcmp(str[0], "env")))
        return (0);
    if (!(ft_strcmp(str[0], "exit")))
        return (free_all_node(node), free_all_ul_split(envp), ft_print("\nexit", 0), exit(127), 0);
    return (1);
}

void    read_input(char **envp)
{
    char *command;
	t_node *node;
	t_node *tmp;

    baner();
    while (1)
    {
        node = NULL;
        command = readline("\033[31m╔══[root@nightmare]—[/dev/null]\n╚═\033[5m♱\033[0m\033[31m> \033[0m▄︻デ══━一💥 > ");
        if (!command)
        {
            ft_print("\nexit", 0);
            free_all_ul_split(envp);
            exit (127);
        }
        if (command)
            add_history(command);
        if(command_analyze(command) == 0)
			command_tokenization(&node, command);
        tmp = node;
        while (tmp)
        {
            if(check_command((tmp)->command, envp, node))
                exe((tmp)->command, envp);
            tmp = (tmp) -> next;
        }
        free_all_node(node);
    }
}
