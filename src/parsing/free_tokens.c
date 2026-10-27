#include "../../minishell.h"

void free_arr(t_command *arr, int i)
{
    if (!arr)
        return;
    while (i >= 0)
    {
        free(arr[i].command);
        arr[i].command = NULL;
        i--;
    }
    free(arr);
}
