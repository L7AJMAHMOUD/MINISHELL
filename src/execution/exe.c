#include "../../minishell.h"
#include <string.h>

static void execution_error(char *command, int error)
{
    fprintf(stderr, "minishell: %s: %s\n", command, strerror(error));
    _exit(error == ENOENT || error == ENOTDIR ? 127 : 126);
}

static void execute_path(char *path, char **command, char **envp)
{
    struct stat info;

    if (!stat(path, &info) && S_ISDIR(info.st_mode))
        execution_error(command[0], EISDIR);
    execve(path, command, envp);
}

void execute_external(t_node *node, char **envp, t_data *data)
{
    char *path;
    char *end;
    char *candidate;
    size_t length;
    int denied = 0;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (ft_strchr(node->command[0], '/'))
    {
        execute_path(node->command[0], node->command, envp);
        execution_error(node->command[0], errno);
    }
    path = get_variable("PATH", envp, data);
    if (!path)
    {
        execute_path(node->command[0], node->command, envp);
        execution_error(node->command[0], errno);
    }
    while (path && *node->command[0])
    {
        end = strchr(path, ':');
        length = end ? (size_t)(end - path) : strlen(path);
        candidate = malloc(length + strlen(node->command[0]) + 2);
        if (!candidate)
            execution_error(node->command[0], ENOMEM);
        memcpy(candidate, path, length);
        candidate[length] = '/';
        strcpy(candidate + length + (length != 0), node->command[0]);
        execve(candidate, node->command, envp);
        if (errno == EACCES)
            denied = 1;
        else if (errno != ENOENT && errno != ENOTDIR)
            execution_error(node->command[0], errno);
        free(candidate);
        path = end ? end + 1 : NULL;
    }
    if (denied)
        execution_error(node->command[0], EACCES);
    fprintf(stderr, "minishell: %s: command not found\n", node->command[0]);
    _exit(127);
}

int shell_wait_status(int status)
{
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

void exe(char **envp, t_node *node, t_data *data)
{
    pid_t pid = fork();
    int status;

    if (pid < 0)
    {
        data->status = 1;
        return (perror("minishell: fork"));
    }
    if (!pid)
        execute_external(node, envp, data);
    status = wait_for_child(pid, data);
    data->status = shell_wait_status(status);
    if (WIFSIGNALED(status) && data->interactive)
    {
        if (WTERMSIG(status) == SIGQUIT)
            ft_print("Quit", 0);
        else if (WTERMSIG(status) == SIGINT)
            write(STDERR_FILENO, "\n", 1);
    }
}
