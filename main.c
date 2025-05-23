/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:20:22 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/23 08:55:11 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **read_stock(char **envp)
{
    int i;
    int j;
    char **str;

    j = 0;
    while (envp[j])
    {
        j++;
    }
    str = malloc((j + 1) * sizeof(char *));
    j = 0;
    while(envp[j])
    {
        i = 0;
        str[j] = malloc(ft_strlen(envp[j]) +1);
        while(envp[j][i])
        {
            str[j][i] = envp[j][i];
            i++;
        }
        str[j][i] = 0;
        j++;
    }
    str[j] = 0;
    return str;
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    envp = read_stock(envp);
    if (ac == 1)
        read_input(&envp);
    else
        invalid_param();
}