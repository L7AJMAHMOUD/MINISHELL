#include "../../minishell.h"

char *ft_strdup(char *src)
{
    size_t i;
    char *h;

    i = 0;
    if (!src)
        return (0);
    h = malloc(ft_strlen(src) * sizeof(char) + 1);
    if (!h)
        return (0);
    while (src[i])
    {
        h[i] = src[i];
        i++;
    }
    h[i] = '\0';
    return (h);
}
