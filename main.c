/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:20:22 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/12 10:37:02 by abkaram          ###   ########.fr       */
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
        j++;
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
    t_data data;
    char buff[BUFFER_SIZE];

    if(!getcwd(buff, BUFFER_SIZE))
    {
        ft_print("minishell : Erreur initialisation",0);
        return 1;
    }
    data.pwd = ft_strdup(buff);
    data.path = ft_strdup("/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin");
    if (!data.path)
    {
        free(data.pwd);
        ft_print("minishell : Erreur initialisation",0);
        return 1;
    }
    if (ac == 1)
	{
		envp = read_stock(envp);
        read_input(&envp, &data);
	}
    else
        invalid_param();
}
