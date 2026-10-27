#include "../../minishell.h"

char *join_strings(char *s1, char *s2)
{
    int i;
    int j;
    char *loc;

    i = 0;
    j = 0;
    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    loc = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if (!loc)
        return (NULL);
    while (s1[i])
        loc[j++] = s1[i++];
    i = 0;
    while (s2[i])
        loc[j++] = s2[i++];
    loc[j] = '\0';
    return (loc);
}

char *ft_strchr(const char *str, int c)
{
    while (*str && *str != (char)c)
        str++;
    if (*str == (char)c)
        return ((char *)str);
    return (NULL);
}
