#include "minishell.h"



void    bash_sig_handler(int sig)
{
    if (sig == 2)
    {
        write(1, "\n\n", 2);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();   
    }
}