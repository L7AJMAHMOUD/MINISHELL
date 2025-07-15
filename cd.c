/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:32:43 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/15 12:23:03 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *strjoin(char *s1, char *s2)
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

void refrech(char *buff, t_data *data, DIR *dir, char ***envp)
{
    char **tmp;
    char *command;

    command = strjoin(ft_strdup("OLDPWD="), data->pwd);
    free (data->pwd);
    tmp = add_to_envp(*envp, command, 1);
    free(command);
    *envp = tmp;
    data->pwd = ft_strdup(buff);
    command = strjoin(ft_strdup("PWD="), data->pwd);
    tmp = add_to_envp(*envp, command, 1);
    free(command);
    *envp = tmp;
}

void cd(char ***envp, char **arg, t_data *data)
{
    char buff[BUFFER_SIZE];
    char *str;
    char *tmp = NULL;
    int i;
    DIR *dir;

    if (!arg || !arg[0])
    {
        str = getenv("HOME");
        if (!str || chdir(str) != 0)
            return(ft_print("minishell: HOME not set", 0));
        refrech(buff, data, dir, envp);
        return ;
    }
    i = 0;
    while (arg[i])
    {
        tmp = strjoin(tmp, arg[i]);
        if (arg[i + 1])
            tmp = strjoin(tmp, " ");
        i++;
    }
    dir = opendir(tmp);
    if (!dir)
    {
        if (i != 1)
        {
            ft_print("minishell: cd: too many arguments", 0);
            return;
        }
        return(perror("minishell"));
    }
    chdir(tmp);
    str = getcwd(buff, BUFFER_SIZE);
    if (str)
        return (refrech(buff, data, dir, envp), (void)closedir(dir));
    perror("cd : erreur de détermination du répertoire actuel : \
    getcwd : ne peut accéder aux répertoires parents ");
    data->pwd = strjoin(data->pwd, "/..");
}
