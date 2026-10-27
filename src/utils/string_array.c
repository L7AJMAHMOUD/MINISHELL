#include "../../minishell.h"

size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

int ft_strcmp(char *s1, char *s2)
{
    size_t i;

    i = 0;
    while (s1[i] == s2[i] && s1[i])
        i++;
    return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

void free_all_ul_split(char **str)
{
    int i;

    if (!str)
        return;
    i = 0;
    while (str[i])
    {
        free(str[i]);
        str[i++] = NULL;
    }
    free(str);
    str = NULL;
}
