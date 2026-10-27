#include "../../minishell.h"

int strlen_until_special(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (ft_isalnum(str[i]) || str[i] == '_')
        i++;
    return (i);
}

char *get_variable(char *str, char **envp, t_data *data)
{
    int i;
    int len;
    char *equal_pos;

    i = 0;
    if (!str || !envp)
        return (NULL);
    len = strlen_until_special(str);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
        {
            equal_pos = ft_strchr(envp[i], '=');
            if (equal_pos)
                return (equal_pos + 1);
        }
        i++;
    }
    if (ft_strcmp("PATH", str) == 0 && data->path)
        return (data->path);
    return (NULL);
}
