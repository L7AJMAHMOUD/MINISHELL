#include "../../minishell.h"

int redirect_input_fd(char **command, t_command *arr, t_data *data, int i)
{
    int fd;

    if (!command[i + 1] || arr[i + 1].ex == -1)
    {
        data->status = 1;
        return (print_err(arr, i), -1);
    }
    if (ft_strcmp(command[i], "<") == 0 && arr[i].q == 0)
    {
        fd = open(command[i + 1], O_RDONLY, 0644);
        if (fd == -1)
        {
            data->status = 1;
            write(2, "minishell : ", sizeof("minishell : ") - 1);
            write(2, command[i + 1], ft_strlen(command[i + 1]));
            write(2, " : ", sizeof(" : ") - 1);
            return (perror(NULL), -1);
        }
        if (dup2(fd, 0) == -1)
            return (perror("dup2 failed"), -1);
        if (close(fd) == -1)
            return (perror("close failed"), -1);
    }
    return (0);
}
