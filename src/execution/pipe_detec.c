#include "../../minishell.h"

int pipe_detector(char *command)
{
    int i;

    i = 0;
    while (command[i])
    {
        skip_inside_quotes(command, &i);
        if (command[i] == PIPE_CHAR)
        {
            i++;
            while (command[i] == SPACE_CHAR)
                i++;
            if (command[i] == '\0')
                return (-1);
        }
        else
            i++;
    }
    return (0);
}

int max_pipe_detector(char *command)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (command[i])
    {
        skip_inside_quotes(command, &i);
        if (command[i] == PIPE_CHAR)
            j++;
        i++;
    }
    if (j > 1024)
        return (-1);
    return (0);
}
