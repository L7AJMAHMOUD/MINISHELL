/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:20:22 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/16 12:12:57 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **read_stock(char **envp, t_data *data)
{
    int i;
    int j;
    char **str;

    j = 0;
    if (!envp)
    {
        str = malloc((3 + 1) * sizeof(char *));
        j = 0;
        if (!str)
            return (NULL);
        str[j] = ft_strdup("OLDPWD");
        str[j++] = join_strings("PWD", data->pwd);
        str[j++] = ft_strdup("SHLVL=1");
        str[j] = 0;
        return str;
    }
    while (envp[j])
        j++;
    str = malloc((j + 1) * sizeof(char *));
    j = 0;
    if (!str)
        return (NULL);
    while(envp[j])
    {
        i = 0;
        str[j] = malloc(ft_strlen(envp[j]) +1);
        if (!str[i])
            return (free_all_ul_split(str), NULL);
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
     if (!data.pwd)
    {
		free(data.pwd);
        ft_print("minishell : Erreur initialisation",0);
        return 1;
    }
    data.path = ft_strdup("/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin");
    if (!data.path)
    {
        free(data.pwd);
        ft_print("minishell : Erreur initialisation",0);
        return 1;
    }
    data.pid = malloc(2000 * sizeof(int));
    if (!data.pid)
    {
        free(data.pwd);
        free(data.path);
        ft_print("minishell : Erreur initialisation",0);
        return 1;
    }
	data.status = 0;
    if (ac == 1)
	{
        envp = read_stock(envp, &data);
        if (!envp)
            return (free(data.pwd), free(data.path), 1);
        read_input(&envp, &data);
	}
    else
        invalid_param();
}
