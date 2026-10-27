#include "../../minishell.h"

/* Read only the current line: children must retain access to unread stdin. */
char *read_shell_line(t_data *data, const char *prompt)
{
    char *line;
    char *grown;
    char c;
    size_t length = 0;
    size_t capacity = 128;
    ssize_t count;

    if (data->interactive)
        return (readline(prompt));
    line = malloc(capacity);
    if (!line)
        return (data->status = 1, NULL);
    while (1)
    {
        count = read(STDIN_FILENO, &c, 1);
        if (count < 0 && errno == EINTR)
            continue;
        if (count < 0)
            return (perror("minishell: read"), free(line), data->status = 1, NULL);
        if (!count || c == '\n')
            break;
        if (length + 1 == capacity)
        {
            capacity *= 2;
            grown = realloc(line, capacity);
            if (!grown)
                return (free(line), data->status = 1, NULL);
            line = grown;
        }
        line[length++] = c;
    }
    if (!count && !length)
        return (free(line), NULL);
    line[length] = '\0';
    return (line);
}
