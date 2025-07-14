/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:32:43 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/06 17:15:15 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char    *strjoin(char *s1, char *s2)
{
    size_t    k;
    size_t    j;
    char    *str;

    j = 0;
    k = 0;
    if (!s2 && !s1)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
    if (str == NULL)
        return (0);
    while (s1[j])
    {
        str[j] = s1[j];
        j++;
    }
    while (s2[k])
        str[j++] = s2[k++];
    str[j] = '\0';
    free(s1);
    return (str);
}

void cd(char ***envp, char *arg, t_data *data)
{
    char buff[BUFFER_SIZE];
    char *tmp;
    int i;
    char *str;
    DIR *dir;

    str = getcwd(buff, BUFFER_SIZE);
    if (str)
    {
        printf("hello\n");
        if (!arg)
        {
            tmp = getenv("HOME");
            if (!tmp || chdir(tmp) != 0)
            {
                perror("minishell");
                return;
            }
            free (data->pwd);
            data->pwd = ft_strdup(buff);
            return;
        }
        dir = opendir(arg);
        if (!dir)
        {
            perror("minishell");
            return;
        }
        chdir(arg);
        free (data->pwd);
        str = getcwd(buff, BUFFER_SIZE);
        data->pwd = ft_strdup(buff);
        closedir(dir);
        return ;
    }
    perror("minishell");
    data->pwd = strjoin(data->pwd, "/..");
    if (access(data->pwd, F_OK) == 0)
    {
        /////////////////////////////////////////////////////////////////////////////////////
        chdir(data->pwd);
        free (data->pwd);
        str = getcwd(buff, BUFFER_SIZE);
        data->pwd = ft_strdup(buff);
        return ;
    }
}
