#include "../../minishell.h"

void ft_print(char *message, int number)
{
    if (number)
        fprintf(stderr, "%s : %d\n", message ? message : "(null)", number);
    else
        fprintf(stderr, "%s\n", message ? message : "(null)");
}
