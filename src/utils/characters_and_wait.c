#include "../../minishell.h"

int ft_isalpha(int c)
{
    if (c >= 65 && c <= 90)
        return (1);
    if (c >= 97 && c <= 122)
        return (1);
    return (0);
}

int ft_isalnum(int c)
{
    if (c >= 48 && c <= 57)
        return (1);
    if (c >= 65 && c <= 90)
        return (1);
    if (c >= 97 && c <= 122)
        return (1);
    return (0);
}

int wait_for_child(pid_t pid, t_data *data)
{
    int status;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    status = 0;
    while (waitpid(pid, &status, 0) < 0)
    {
        if (errno != EINTR)
            return (signal_init(data), 1 << 8);
    }
    signal_init(data);
    return (status);
}
