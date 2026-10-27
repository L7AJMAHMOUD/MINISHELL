#include "../../minishell.h"

static t_data *shell_data;

void bash_sig_handler(int signum)
{
    (void)signum;
    shell_data->status = 130;
    write(STDOUT_FILENO, "\n", 1);
    if (shell_data->interactive)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void signal_init(t_data *data)
{
    shell_data = data;
    rl_catch_signals = 0;
    if (signal(SIGINT, bash_sig_handler) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("minishell: signal");
}
