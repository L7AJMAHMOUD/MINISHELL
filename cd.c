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
    return (str);
}

void cd(char ***envp, char *arg)
{
    char buff[BUFFER_SIZE];
    char *tmp;
    char **tmp1;
    char *str;
    DIR *dir;
    
    if (arg)
    {
        dir = opendir(arg);
        if (!dir)
        {
            perror(arg);
            return ;
        }
    }
    if(!getcwd(buff, BUFFER_SIZE))
        perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
    if (!arg)
    {    
        if (!getenv("HOME") || chdir(getenv("HOME")))
            perror("chdir");
        return ;
    }
    if (arg[0] == '/')
    {
        chdir (arg);
        tmp1 = add_to_envp(*envp, arg, 1);
        *envp = tmp1;
    }
    else
    {
        tmp = strjoin(buff, "/");
        str = strjoin(tmp, arg);
        if (chdir (str))
        {
            tmp1 = add_to_envp(*envp, str, 1);
            *envp = tmp1;
        }
        free(tmp);
        free(str);
    }
    closedir(dir);
}