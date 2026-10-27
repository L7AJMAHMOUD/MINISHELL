#include "../../minishell.h"

int is_echo_n_flag(char *str)
{
    int i;

    i = 0;
    if (str[i++] != '-' || !str[i])
        return (0);
    while (str[i])
    {
        if (str[i++] != 'n')
            return (0);
    }
    return (1);
}

void print_env_value_escaped(char *str, int k, int i)
{
    while (str && str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    if (k != 0)
        write(1, " ", sizeof(" ") - 1);
}

void echo(char **str, t_data *data, int p)
{
    int i;

    i = 1;
    while (str && str[i] && is_echo_n_flag(str[i]))
    {
        i++;
        p = -1;
    }
    while (str && str[i])
    {
        if (str[i + 1])
            print_env_value_escaped(str[i], 1, 0);
        else
            print_env_value_escaped(str[i], 0, 0);
        i++;
        if (!str[i] && p == 0)
            write(1, "\n", sizeof("\n") - 1);
    }
    if (!str[1])
        write(1, "\n", sizeof("\n") - 1);
    data->status = 0;
}

void pwd(t_data *data)
{
    char buff[BUFFER_SIZE];

    if (!getcwd(buff, BUFFER_SIZE))
    {
        data->status = 0;
        printf("%s\n", data->pwd);
        return;
    }
    data->status = 0;
    printf("%s\n", buff);
}
