/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/26 10:37:52 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D')
			break ;
		i++;
	}
	// if (!envp[i])
    //     ft_printf("pwd not disponible\n", 0);
    printf("%s\n",&envp[i][4]);
}

void free_all_node(t_node *node)
{
    while (node)
    {
        free_all_ul_split(node->command);
        free(node);
        node = node->next;
    }
    
}

int check_command(char **str, char **envp)
{
    if (!(ft_strcmp(str[0], "echo")))
        return (0);
    if (!(ft_strcmp(str[0], "cd")))
        return (0);
    if (!(ft_strcmp(str[0], "pwd")))
        return (pwd(envp), 0);
    if (!(ft_strcmp(str[0], "export")))
        return (0);
    if (!(ft_strcmp(str[0], "unset")))
        return (0);
    if (!(ft_strcmp(str[0], "env")))
        return (0);
    if (!(ft_strcmp(str[0], "exit")))
        return (0);
    return (1);
}

void    read_input(char **envp)
{
    char *command;
	t_node *node;
	t_node *tmp;

    while (1)
    {
        node = NULL;
        command = readline("▄︻デ══━一💥 > ");
        if (!command)
        {
            printf("\nexit\n");
            exit (127);
        }
        if (command)
            add_history(command);
        if(command_analyze(command) == 0)
			command_tokenization(&node, command);
        tmp = node;
        while (tmp)
        {
            if(check_command((tmp)->command, envp))
                exe((tmp)->command, envp);
            tmp = (tmp) -> next;
        }
        free_all_node(node);
    }
}
