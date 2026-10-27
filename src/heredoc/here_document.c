#include "../../minishell.h"

static void collect_document(t_node *node, int i, t_data *data, int fd)
{
    char *line;
    char *expanded;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        line = read_shell_line(data, "> ");
        if (!line)
        {
            ft_print("minishell: warning: here-document delimited by end-of-file", 0);
            break;
        }
        if (!ft_strcmp(line, node->arr[i + 1].command))
        {
            free(line);
            break;
        }
        expanded = line;
        if (!node->arr[i + 1].k)
            expanded = expand_str(line, *data->envp, data);
        if (expanded)
            write(fd, expanded, ft_strlen(expanded));
        write(fd, "\n", 1);
        if (expanded != line)
            free(expanded);
        free(line);
    }
    close(fd);
    _exit(0);
}

static int prepare_document(t_node *node, int i, t_data *data)
{
    char template[] = "/tmp/minishell-heredoc-XXXXXX";
    int fd;
    int status = 1 << 8;
    pid_t pid;

    fd = mkstemp(template);
    if (fd < 0)
        return (perror("minishell: heredoc"), data->status = 1, -1);
    unlink(template);
    fcntl(fd, F_SETFD, FD_CLOEXEC);
    pid = fork();
    if (pid < 0)
        return (close(fd), perror("minishell: fork"), data->status = 1, -1);
    if (!pid)
        collect_document(node, i, data, fd);
    signal(SIGINT, SIG_IGN);
    while (waitpid(pid, &status, 0) < 0 && errno == EINTR)
        ;
    signal_init(data);
    if (!WIFEXITED(status) || WEXITSTATUS(status))
    {
        data->status = WIFSIGNALED(status) ? 128 + WTERMSIG(status) : WEXITSTATUS(status);
        return (close(fd), -1);
    }
    if (node->hd >= 0)
        close(node->hd);
    node->hd = fd;
    if (lseek(fd, 0, SEEK_SET) == -1)
        return (perror("minishell: heredoc"), data->status = 1, -1);
    return (0);
}

int prepare_heredocs(t_node *node, t_data *data)
{
    int i;

    while (node)
    {
        i = 0;
        while (node->command && node->command[i])
        {
            if (!node->arr[i].q && !ft_strcmp(node->command[i], "<<"))
            {
                if (prepare_document(node, i, data) < 0)
                    return (-1);
                i++;
            }
            i++;
        }
        node = node->next;
    }
    return (0);
}
