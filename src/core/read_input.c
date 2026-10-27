#include "../../minishell.h"

int check_command(char **str, char ***envp, t_node *node, t_data *data)
{
    if (!str || !*str)
        return (data->status = 0, 0);
    if (!(ft_strcmp(str[0], "echo")))
        return (echo(str, data, 0), 0);
    if (!(ft_strcmp(str[0], "cd")))
        return (cd(envp, &str[1], data), 0);
    if (!(ft_strcmp(str[0], "pwd")))
        return (pwd(data), 0);
    if (!(ft_strcmp(str[0], "export")))
        return (export(envp, node->command, data), 0);
    if (!(ft_strcmp(str[0], "unset")))
        return (unset(envp, str, data), 0);
    if (!(ft_strcmp(str[0], "env")))
        return (print_env(*envp, node->command, data), 0);
    if (!(ft_strcmp(str[0], "exit")))
        return (ft_exit(envp, node, data), 0);
    return (1);
}

static void handle_null_command(char ***envp, t_data *data)
{
    if (data->interactive)
    {
        ft_print("exit", 0);
        write_history(".minishell_history");
    }
    rl_clear_history();
    if (*envp)
        free_all_ul_split(*envp);
    if (data->path)
        free(data->path);
    if (data->pwd)
        free(data->pwd);
    if (data->pid)
        free(data->pid);
    exit(data->status);
}

static void execute_command(t_node *node, char ***envp, t_data *data)
{
    t_node *tmp;
    int s_in;
    int s_out;

    if (!node)
        return;
    data->envp = envp;
    if (prepare_heredocs(node, data) == -1)
    {
        free_all_node(node);
        return;
    }
    tmp = node;
    if (node->next)
    {
        pip(envp, data, node);
        free_all_node(node);
        return;
    }
    s_in = dup(STDIN_FILENO);
    s_out = dup(STDOUT_FILENO);
    if (s_in < 0 || s_out < 0)
    {
        if (s_in >= 0)
            close(s_in);
        if (s_out >= 0)
            close(s_out);
        data->status = 1;
        free_all_node(node);
        return (perror("minishell: dup"));
    }
    fcntl(s_in, F_SETFD, FD_CLOEXEC);
    fcntl(s_out, F_SETFD, FD_CLOEXEC);
    tmp->command = apply_redirections(tmp, envp, data);
    if (tmp->command && check_command(tmp->command, envp, node, data))
    {
        exe(*envp, node, data);
    }
    dup2(s_in, STDIN_FILENO);
    dup2(s_out, STDOUT_FILENO);
    close(s_in);
    close(s_out);
    free_all_node(node);
}

void read_input(char ***envp, t_data *data)
{
    char *command;
    t_node *node;

    signal_init(data);
    while (1)
    {
        node = NULL;
        data->id = 0;
        command = read_shell_line(data, "minishell$ ");
        if (!command)
            handle_null_command(envp, data);
        if (command_analyze(command, data) == 0)
        {
            if (data->interactive)
                add_history(command);
            command_tokenization(&node, command, *envp, data);
            execute_command(node, envp, data);
        }
        free(command);
    }
}
