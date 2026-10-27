#include "../../minishell.h"
#include <ctype.h>
#include <string.h>

/* Heredoc text expands variables without quote removal or field splitting. */
char *expand_str(char *input, char **envp, t_data *data)
{
    char *result = ft_strdup("");
    char *start;
    char *name;
    char *value;
    char literal[2] = {0};
    char status[16];

    while (result && *input)
    {
        value = literal;
        literal[0] = *input++;
        if (literal[0] == '$' && *input == '?')
        {
            snprintf(status, sizeof(status), "%d", data->status);
            value = status;
            input++;
        }
        else if (literal[0] == '$' && (isalpha((unsigned char)*input) || *input == '_'))
        {
            start = input;
            while (isalnum((unsigned char)*input) || *input == '_')
                input++;
            name = strndup(start, input - start);
            if (!name)
                return (free(result), NULL);
            value = get_variable(name, envp, data);
            free(name);
        }
        else if (literal[0] == '$' && isdigit((unsigned char)*input))
        {
            input++;
            value = "";
        }
        result = strmerge_and_free(result, value);
    }
    return (result);
}
