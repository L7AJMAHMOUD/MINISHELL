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

void refrech(char *buff, t_data *data, DIR *dir)
{
    free (data->pwd);
    data->pwd = ft_strdup(buff);
    closedir(dir);
}

void cd(char ***envp, char *arg, t_data *data)
{
    char buff[BUFFER_SIZE];
    char *str;
    DIR *dir;

    // if (arg[1])
    //     return(ft_print("minishell: cd : too many args", 0));
    if (!arg)
    {
        str = getenv("HOME");
        if (!str || chdir(str) != 0)
            return(ft_print("minishell: HOME not set", 0));
        free (data->pwd);
        data->pwd = ft_strdup(buff);
        return ;
    }
    dir = opendir(arg);
    if (!dir)
        return(perror("minishell"));
    chdir(arg);
    str = getcwd(buff, BUFFER_SIZE);
    if (str)
        return (refrech(buff, data, dir));
    perror("cd : erreur de détermination du répertoire actuel : \
    getcwd : ne peut accéder aux répertoires parents ");
    data->pwd = strjoin(data->pwd, "/..");
}
