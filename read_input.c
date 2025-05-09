/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/09 10:30:36 by user01           ###   ########.fr       */
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

char **add_to_envp(char **envp, char *ligne)
{
    int i;
    int j;
    char **str;

    j = 0;
    while (envp[j])
        j++;
    str = malloc((j + 2) * sizeof(char *));
    j = 0;
    while(envp[j])
    {
        i = 0;
        str[j] = malloc(ft_strlen(envp[j]) + 1);
        while(envp[j][i])
        {
            str[j][i] = envp[j][i];
            i++;
        }
        str[j][i] = 0;
        j++;
    }
    i = 0;
    str[j] = malloc(ft_strlen(ligne) + 1);
    while(ligne[i])
    {
        str[j][i] = ligne[i];
        i++;
    }
    str[j++][i] = 0;
    str[j] = NULL;
    // free_all_ul_split(envp);
    return str;
}

void export(char ***envp, char **command)
{
    int i;
    int j;
    char **tmp;
    int k;

    i = 0;
    j = 1;
    tmp = *envp;
    if (!command[1])
        while (tmp[i])
        {
            j = 0;
            k = 0;
            write(1, "declare -x ", 12); 
            while(tmp[i][j])
            {
                write(1, &tmp[i][j], 1);
                if (tmp[i][j] == '=' || (!tmp[i][j + 1] && k == 1))
                {
                    write(1, "\"", 1);
                    k = 1;
                }
                j++;
            }
            write(1, "\n", 1);
            i++;
        }
    else
    {
        while(command[j])
        {
            tmp = add_to_envp(*envp, command[j++]);
            *envp = tmp;
        }
    }
        
}

int check_command(char **str, char ***envp, t_node *node)
{
    if (!(ft_strcmp(str[0], "echo")))
        return (echo(str, 1, *envp), 0);
    if (!(ft_strcmp(str[0], "cd")))
        return (0);
    if (!(ft_strcmp(str[0], "pwd")))
        return (pwd(*envp, 1), 0);
    if (!(ft_strcmp(str[0], "export")))
        return (export(envp, node->command), 0);
    if (!(ft_strcmp(str[0], "unset")))
        return (0);
    if (!(ft_strcmp(str[0], "env")))
        return (0);
    if (!(ft_strcmp(str[0], "exit")))
        return (free_all_node(node), free_all_ul_split(*envp), ft_print("\nexit", 0), exit(127), 0);
    return (1);
}

void    read_input(char ***envp)
{
    char *command;
	t_node *node;
	t_node *tmp;
    char *str;

    // baner();
    while (1)
    {
        node = NULL;
		printf("\033[31m╔══[root@nightmare]—[");
		pwd(*envp, 0);
		printf("]\n");
        command = readline("╚═\033[5m\033[0m\033[31m> \033[0m▄︻デ══━一💥 > ");
        if (!command)
        {
            ft_print("\nexit", 0);
            free_all_ul_split(*envp);
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
                exe((tmp)->command, *envp);
            tmp = (tmp) -> next;
        }
        free_all_node(node);
    }
}
