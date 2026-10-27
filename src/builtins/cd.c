#include "../../minishell.h"

char *strmerge_and_free(char *s1, char *s2)
{
    size_t k;
    size_t j;
    char *str;

    j = 0;
    k = 0;
    if (!s2 && !s1)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (s1);
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
    return (s1 = NULL, str);
}

void update_pwd_vars(char *buff, t_data *data, char ***envp)
{
    char **tmp;
    char *command;

    command = strmerge_and_free(ft_strdup("OLDPWD="), data->pwd);
    free(data->pwd);
    tmp = add_to_envp(*envp, command, 0, NULL);
    free(command);
    *envp = tmp;
    data->pwd = ft_strdup(buff);
    command = strmerge_and_free(ft_strdup("PWD="), data->pwd);
    tmp = add_to_envp(*envp, command, 0, NULL);
    free(command);
    *envp = tmp;
}

void cd(char ***envp, char **arg, t_data *data)
{
    char buff[BUFFER_SIZE];
    char *target;
    int print_path = 0;

    data->status = 1;
    if (arg[0] && arg[1])
        return (ft_print("minishell: cd: too many arguments", 0));
    if (!arg[0])
        target = ft_strdup(get_variable("HOME", *envp, data));
    else if (!ft_strcmp(arg[0], "-"))
    {
        target = ft_strdup(get_variable("OLDPWD", *envp, data));
        print_path = 1;
    }
    else
        target = ft_strdup(arg[0]);
    if (!target || !*target)
    {
        free(target);
        return (ft_print("minishell: cd: directory variable is not set", 0));
    }
    if (chdir(target) == -1)
        return (free(target), perror("minishell: cd"));
    free(target);
    if (!getcwd(buff, sizeof(buff)))
        return (perror("minishell: cd: getcwd"));
    update_pwd_vars(buff, data, envp);
    if (print_path)
        puts(buff);
    data->status = 0;
}
