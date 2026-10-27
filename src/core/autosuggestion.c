#include "../../minishell.h"

static char *g_suggestion = NULL;

static int autosuggestion_hook(void)
{
    char *line;
    HIST_ENTRY *entry;

    line = rl_line_buffer;
    if (g_suggestion)
        free(g_suggestion);
    g_suggestion = NULL;
    if (line && *line && rl_point == rl_end)
    {
        history_set_pos(history_length);
        while ((entry = previous_history()))
        {
            if (ft_strncmp(entry->line, line, ft_strlen(line)) == 0 &&
                ft_strlen(entry->line) > ft_strlen(line))
            {
                g_suggestion = ft_strdup(entry->line);
                break;
            }
        }
    }
    if (g_suggestion)
    {
        printf("\033[s\033[90m%s\033[0m\033[u", g_suggestion + rl_point);
        fflush(stdout);
    }
    return (0);
}

static int accept_suggestion_handler(int count, int key)
{
    (void)count;
    (void)key;
    if (g_suggestion && rl_point == rl_end)
    {
        rl_replace_line(g_suggestion, 0);
        rl_end_of_line(0, 0);
        free(g_suggestion);
        g_suggestion = NULL;
    }
    else
    {
        if (rl_point < rl_end)
        {
            rl_point++;
            rl_redisplay();
        }
    }
    return (0);
}

void init_autosuggestions(void)
{
    rl_event_hook = autosuggestion_hook;
    rl_bind_keyseq("\033[C", accept_suggestion_handler);
}
