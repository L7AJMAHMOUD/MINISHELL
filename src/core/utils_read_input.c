#include "../../minishell.h"

void free_all_node(t_node *node)
{
    t_node *tmp;

    while (node)
    {
        tmp = node->next;
        if (node->hd >= 0)
            close(node->hd);
        free_all_ul_split(node->command);
        free_arr(node->arr, node->i - 1);
        free(node);
        node = tmp;
    }
}

void print_env(char **envp, char **command, t_data *data)
{
    int i;

    i = 0;
    if (command[1])
    {
        ft_print("minishell: env: arguments are not supported", 0);
        data->status = 125;
        return;
    }
    else
        while (envp && envp[i])
        {
            if (ft_strchr(envp[i], '='))
                printf("%s\n", envp[i]);
            i++;
        }
    data->status = 0;
}

static int exit_number(char *value, int *status)
{
    char *end;
    long long number;

    errno = 0;
    number = strtoll(value, &end, 10);
    if (end == value || errno == ERANGE)
        return (0);
    while (*end == ' ' || (*end >= '\t' && *end <= '\r'))
        end++;
    if (*end)
        return (0);
    *status = (unsigned char)number;
    return (1);
}

void ft_exit(char ***envp, t_node *node, t_data *data)
{
    int status = data->status;

    if (data->interactive)
        ft_print("exit", 0);
    if (node->command[1] && !exit_number(node->command[1], &status))
    {
        ft_print("minishell: exit: numeric argument required", 0);
        status = 2;
    }
    else if (node->command[1] && node->command[2])
    {
        ft_print("minishell: exit: too many arguments", 0);
        data->status = 1;
        return;
    }
    if (data->interactive)
        write_history(".minishell_history");
    rl_clear_history();
    free_all_ul_split(*envp);
    free_all_node(node);
    free(data->path);
    free(data->pwd);
    free(data->pid);
    exit(status);
}
