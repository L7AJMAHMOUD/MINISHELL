#include "../../minishell.h"
#include <ctype.h>
#include <string.h>

typedef struct s_word
{
    char **fields;
    size_t count;
    char *text;
    size_t length;
    int present;
    int quoted;
} t_word;

static int append_char(t_word *word, char c)
{
    char *grown = realloc(word->text, word->length + 2);

    if (!grown)
        return (-1);
    word->text = grown;
    word->text[word->length++] = c;
    word->text[word->length] = 0;
    word->present = 1;
    return (0);
}

static int finish_field(t_word *word)
{
    char **grown;

    if (!word->present)
        return (0);
    grown = realloc(word->fields, (word->count + 2) * sizeof(char *));
    if (!grown)
        return (-1);
    word->fields = grown;
    if (!word->text)
        word->text = ft_strdup("");
    if (!word->text)
        return (-1);
    word->fields[word->count++] = word->text;
    word->fields[word->count] = NULL;
    word->text = NULL;
    word->length = 0;
    word->present = 0;
    return (0);
}

static int expand_variable(t_word *word, char **cursor, char **envp, t_data *data, int quoted)
{
    char *start = ++*cursor;
    char *name;
    char *value;
    char status[16];
    size_t i;

    if (**cursor == '?')
    {
        snprintf(status, sizeof(status), "%d", data->status);
        value = status;
        (*cursor)++;
    }
    else if (isdigit((unsigned char)**cursor))
        return ((*cursor)++, 0);
    else if (isalpha((unsigned char)**cursor) || **cursor == '_')
    {
        while (isalnum((unsigned char)**cursor) || **cursor == '_')
            (*cursor)++;
        name = strndup(start, *cursor - start);
        if (!name)
            return (-1);
        value = get_variable(name, envp, data);
        free(name);
    }
    else
        return (append_char(word, '$'));
    i = 0;
    while (value && value[i])
    {
        if (!quoted && (value[i] == ' ' || value[i] == '\t' || value[i] == '\n'))
        {
            if (finish_field(word) < 0)
                return (-1);
        }
        else if (append_char(word, value[i]) < 0)
            return (-1);
        i++;
    }
    return (0);
}

static int read_word(t_word *word, char **cursor, char **envp, t_data *data, int delimiter)
{
    char quote = 0;
    char c;

    while (**cursor)
    {
        c = **cursor;
        if (!quote && (isspace((unsigned char)c) || c == '|' || c == '<' || c == '>'))
            break;
        if ((c == '\'' || c == '"') && (!quote || quote == c))
        {
            word->quoted = 1;
            word->present = 1;
            quote = quote ? 0 : c;
            (*cursor)++;
        }
        else if (c == '$' && quote != '\'' && !delimiter)
        {
            if (expand_variable(word, cursor, envp, data, quote != 0) < 0)
                return (-1);
        }
        else
        {
            if (append_char(word, c) < 0)
                return (-1);
            (*cursor)++;
        }
    }
    return (finish_field(word));
}

static int append_token(t_node *node, const char *text, int operator, int quoted, int ambiguous)
{
    char **commands;
    t_command *tokens;

    commands = realloc(node->command, (node->i + 2) * sizeof(char *));
    if (!commands)
        return (-1);
    node->command = commands;
    node->command[node->i] = NULL;
    tokens = realloc(node->arr, (node->i + 2) * sizeof(t_command));
    if (!tokens)
        return (-1);
    node->arr = tokens;
    memset(&node->arr[node->i], 0, 2 * sizeof(t_command));
    node->command[node->i] = ft_strdup((char *)text);
    node->arr[node->i].command = ft_strdup((char *)text);
    if (!node->command[node->i] || !node->arr[node->i].command)
    {
        free(node->command[node->i]);
        node->command[node->i] = NULL;
        free(node->arr[node->i].command);
        return (-1);
    }
    node->arr[node->i].q = !operator;
    node->arr[node->i].k = quoted;
    node->arr[node->i].ex = ambiguous;
    node->command[++node->i] = NULL;
    return (0);
}

static t_node *new_node(void)
{
    t_node *node = calloc(1, sizeof(*node));

    if (!node)
        return (NULL);
    node->hd = -1;
    node->command = calloc(1, sizeof(char *));
    if (!node->command)
        return (free(node), NULL);
    return (node);
}

static int add_word(t_node *node, char **cursor, char **envp, t_data *data)
{
    t_word word = {0};
    int redirect = node->i && !node->arr[node->i - 1].q;
    int delimiter = redirect && !ft_strcmp(node->command[node->i - 1], "<<");
    size_t i = 0;
    int result;

    result = read_word(&word, cursor, envp, data, delimiter);
    if (!result && redirect && word.count != 1)
        result = append_token(node, "", 0, word.quoted, -1);
    else
        while (!result && i < word.count)
            result = append_token(node, word.fields[i++], 0, word.quoted, 0);
    free(word.text);
    free_all_ul_split(word.fields);
    return (result);
}

void command_tokenization(t_node **root, char *cursor, char **envp, t_data *data)
{
    t_node *node = new_node();
    char operator[3];
    int failed = !node;

    *root = node;
    while (!failed && *cursor)
    {
        if (isspace((unsigned char)*cursor))
            cursor++;
        else if (*cursor == '|')
        {
            node->next = new_node();
            node = node->next;
            failed = !node;
            cursor++;
        }
        else if (*cursor == '<' || *cursor == '>')
        {
            operator[0] = *cursor++;
            operator[1] = 0;
            operator[2] = 0;
            if (*cursor == operator[0])
                operator[1] = *cursor++;
            failed = append_token(node, operator, 1, 0, 0);
        }
        else
            failed = add_word(node, &cursor, envp, data);
    }
    if (failed)
    {
        free_all_node(*root);
        *root = NULL;
        data->status = 1;
        ft_print("minishell: out of memory", 0);
    }
}
