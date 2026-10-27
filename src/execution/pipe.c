#include "../../minishell.h"

static void pipeline_child(t_node *node, t_node *root, t_data *data, int input, int pipefd[2])
{

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    data->interactive = 0;
    if (input >= 0 && dup2(input, STDIN_FILENO) < 0)
        _exit(1);
    if (input >= 0)
        close(input);
    if (node->next)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) < 0)
            _exit(1);
        close(pipefd[1]);
    }
    node->command = apply_redirections(node, data->envp, data);
    while (root)
    {
        if (root->hd >= 0)
            close(root->hd);
        root->hd = -1;
        root = root->next;
    }
    if (node->command && check_command(node->command, data->envp, node, data))
        execute_external(node, *data->envp, data);
    _exit(data->status);
}

int pip(char ***envp, t_data *data, t_node *root)
{
    t_node *node = root;
    int input = -1;
    int pipefd[2] = {-1, -1};
    int status;
    int failed = 0;
    int i;
    pid_t pid;

    data->envp = envp;
    data->id = 0;
    signal(SIGINT, SIG_IGN);
    while (node)
    {
        if (node->next && pipe(pipefd) < 0)
        {
            failed = 1;
            break;
        }
        pid = fork();
        if (pid < 0)
        {
            if (node->next)
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            failed = 1;
            break;
        }
        if (!pid)
            pipeline_child(node, root, data, input, pipefd);
        data->pid[data->id++] = pid;
        if (input >= 0)
            close(input);
        input = -1;
        if (node->next)
        {
            close(pipefd[1]);
            input = pipefd[0];
        }
        node = node->next;
    }
    if (input >= 0)
        close(input);
    if (failed)
    {
        perror("minishell: pipeline");
        i = 0;
        while (i < data->id)
            kill(data->pid[i++], SIGTERM);
    }
    i = 0;
    while (i < data->id)
    {
        status = 1 << 8;
        while (waitpid(data->pid[i], &status, 0) < 0 && errno == EINTR)
            ;
        i++;
        data->status = shell_wait_status(status);
    }
    if (failed)
        data->status = 1;
    signal_init(data);
    return (failed);
}
