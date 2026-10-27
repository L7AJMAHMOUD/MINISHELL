#include "../../minishell.h"

char **cpt_read_stock(char **str, t_data *data)
{
    int j;

    j = 0;
    str = malloc((3 + 1) * sizeof(char *));
    if (!str)
        return (NULL);
    str[j++] = ft_strdup("OLDPWD");
    str[j++] = join_strings("PWD=", data->pwd);
    str[j++] = ft_strdup("SHLVL=1");
    str[j] = 0;
    return (str);
}

char **read_stock(char **envp, t_data *data, int j, int i)
{
    char **str;

    str = NULL;
    if (!envp[0])
        return (cpt_read_stock(str, data));
    while (envp[j])
        j++;
    str = malloc((j + 1) * sizeof(char *));
    if (!str)
        return (NULL);
    j = 0;
    while (envp[j])
    {
        i = 0;
        str[j] = malloc(ft_strlen(envp[j]) + 1);
        if (!str[j])
            return (free_all_ul_split(str), NULL);
        while (envp[j][i])
        {
            str[j][i] = envp[j][i];
            i++;
        }
        str[j++][i] = 0;
    }
    return (str[j] = 0, str);
}
