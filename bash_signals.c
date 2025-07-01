#include "minishell.h"

void    bash_sig_handler(int sig)
{
    write(1, "\n", 2);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();   
}