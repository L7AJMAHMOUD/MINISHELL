#include "../../minishell.h"

int redirect_parse(char *command)
{
    int i = 0;
    char symbol;

    while (command[i])
    {
        if (command[i] == QUOTE_SINGLE || command[i] == QUOTE_DOUBLE)
            skip_inside_quotes(command, &i);
        else if (command[i] == '<' || command[i] == '>')
        {
            symbol = command[i++];
            if (command[i] == symbol)
                i++;
            while (command[i] && command[i] <= 32)
                i++;
            if (!command[i] || command[i] == '<' || command[i] == '>' || command[i] == '|')
                return (-1);
            continue;
        }
        i++;
    }
    return (0);
}

int redirect_parse_double(char *command)
{
    return (redirect_parse(command));
}
