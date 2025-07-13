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
        if (!arg)
        {
            tmp = getenv("HOME");
            if (!tmp)
                return ;
            chdir (tmp);
            data->pwd = buff;
            return;
        }
        dir = opendir(arg);
        if (!dir)
        {
            perror("minishell");
            return;
        }
        chdir(arg);
        data->pwd = buff;
        closedir(dir);
        return ;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    chdir(data->pwd);
}
