#include "../../minishell.h"

void print_err(t_command *arr, int i)
{
    write(2, "minishell : ", sizeof("minishell : ") - 1);
    write(2, arr[i + 1].command, ft_strlen(arr[i + 1].command));
    write(2, " : ", sizeof(" : ") - 1);
    write(2, "ambiguous redirect\n", sizeof("ambiguous redirect\n") - 1);
}

int append_to_fd(char **command, t_command *arr, t_data *data, int i)
{
    int fd;

    if (ft_strcmp(command[i], ">>") == 0 && arr[i].q == 0)
    {
        if (!command[i + 1] || arr[i + 1].ex == -1)
        {
            return (data->status = 1, print_err(arr, i), -1);
        }
        fd = open(command[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd == -1)
        {
            data->status = 1;
            write(2, "minishell : ", sizeof("minishell : ") - 1);
            write(2, arr[i + 1].command, ft_strlen(arr[i + 1].command));
            write(2, " : ", sizeof(" : ") - 1);
            perror(NULL);
            return (-1);
        }
        if (dup2(fd, 1) == -1)
            return (perror("dup2 failed"), -1);
        if (close(fd) == -1)
            return (perror("close failed"), -1);
    }
    return (0);
}
