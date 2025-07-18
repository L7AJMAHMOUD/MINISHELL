#include "minishell.h"

int validate_pipe_syntax(char *command)
{
    int i;
    int k;
    
    i = 0;
    k = 0;
    while (command[i])
    {
        skip_inside_quotes(command, &i);
        if (command[i] == PIPE_CHAR)
        {
            i++;
            k++;
            if (k > 2)
                return -1;
            while (command[i] && command[i] <= 32)
                i++;
            if (!command[i] || command[i] == PIPE_CHAR)
                return -1;
        }
        else
        {
            k = 0;
            i++;
        }
    }
    return 0;
}
