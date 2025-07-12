/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultra_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/12 09:47:29 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void rev_(char *s)
{
    int i;
    int j;
    int c;

    if (!s)
        return;

    i = 0;
    j = ft_strlen(s) - 1;

    while (i < j)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        i++;
        j--;
    }
}
int count_words(char *s, char sep)
{
    int i = 0;
    int count = 0;
    char quote;

    if (!s)
        return 0;

    while (s[i] && s[i] != PIPE_CHAR)
    {
        while (s[i] == SPACE_CHAR)
            i++;

        if (!s[i] || s[i] == PIPE_CHAR)
            break;

        if (s[i] == QUOTE_SINGLE || s[i] == QUOTE_DOUBLE)
        {
            if (i == 0 || s[i - 1] == SPACE_CHAR || s[i - 1] == sep)
                count++;
            
            quote = s[i++];
            while ((s[i] && s[i] != quote && s[i] != PIPE_CHAR))
                i++;
            if (s[i] == quote)
                i++;
        }
        else if (s[i] != sep)
        {
			if (i == 0 || s[i - 1] == SPACE_CHAR || s[i - 1] == sep)
            	count++;
            while (s[i] && s[i] != sep && s[i] != QUOTE_SINGLE 
                   && s[i] != QUOTE_DOUBLE && s[i] != PIPE_CHAR)
                i++;
        }
        else
        {
            i++;
        }
    }
    return count;
}



void	preparation(char **s, int j)
{
	int i;
	int c;
	int k;
	char *tmp;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == QUOTE_SINGLE || (*s)[i] == QUOTE_DOUBLE)
		{
			c = (*s)[i];
			i++;
			while ((*s)[i] != c)
			{
				i++;
			}
			i++;
			continue;
		}
		if ((*s)[i] == '<' || (*s)[i] == '>' || (*s)[i] == '|')
		{
			k = 0;
			c = (*s)[i];
			while ((*s)[i] == c && (*s)[i])
				i++;
			tmp = ft_strdup(&(*s)[i]);
			(*s)[i] = 0;
			*s = ft_strjoin(*s, tmp);
			i++;
			continue;
		}
		i++;
	}
}

int initialisation(t_command *arr, int word)
{
	int i;
	
	i = 0;
	while(i < word)
	{
		arr[i].command = NULL;
		i++; 
	}
	return 0;
}
static int	ln(char *s)
{
	int	length;
	char c;
	char x;

	c = ' ';
	length = 0;
	while (s[length] && s[length] != c && s[length] != '>' && s[length] != '<')
	{
		if (s[length] == QUOTE_SINGLE || s[length] == QUOTE_DOUBLE)
		{
			x = s[length];
			length++;
			while (s[length] != x && s[length])
			{
				length++;
			}
			length++;
			continue;
		}
		length++;
	}
	while (s[length] == '>' || s[length] == '<')
		length++;
	return (length);
}


char **ft_arr_to_tab(t_command *arr, int words)
{
	char **tab;
	int i;
	int j;

	if (!arr || words <= 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < words)
	{
		if (arr[j].command[0] == 0 && i != 0) //////////////////////////////////////// ls $lsdjljds -l bach tkhdem
		{
			j++;
			words--;
			continue;
		}
		tab[i] = ft_strdup(arr[j].command);
		if (!tab[i])
		{
			while (i--)
			free(tab[i]);
			free(tab);
			return (NULL);
		}
		i++;
		j++;
	}
	tab[i] = NULL;
	i = 0;
	while (i < words)
	{
		free(arr[i++].command);
	}
	free(arr);
	return (tab);
}


char	**ft_ultra_split(char *str, int	i, int		j,char ** envp)
{
	t_command *arr;
	int words;
	int x;
	int k;
	preparation(&str, 0);
	rev_(str);
	preparation(&str, 1);
	rev_(str);
	words = count_words(str, ' ');
	arr = malloc(sizeof(t_command) * words);
	i = initialisation(arr, words);
	i = 0;
	while (j < words)
	{
		x = 0;
		while(str[i] == 32)
		i++;
		arr[j].command=malloc(sizeof(char) * ln(&str[i]) + 1);
		k = i + ln(&str[i]);
		while (i < k)
		{
			arr[j].command[x] = str[i];
			i++;
			x++;
		}
		arr[j].command[x] = 0;
		i++;
		j++;
	}
	// free(str);
	for (int v = 0; v < words; v++)
		arr[v].command = cooking(arr[v].command, envp, v);
	char **tab = ft_arr_to_tab(arr, words);
	return(tab);
}

// int main (int ac, char **av, char **envp)
// {
// 	char *tmp =ft_strdup("ls|ls");
// 	char **str = ft_ultra_split(tmp, 0 ,0, envp);
// 	for(int i = 0;str[i]; i++)
// 		printf("%s\n",str[i]);
// }

// gcc ft_ultra_split.c utils.c split_utils.c split.c