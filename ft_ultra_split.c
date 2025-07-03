/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultra_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/03 13:30:37 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_quotes(char *s, int *length, int *k)
{
	if (s[*length] == '"')
	{
		*k += 2;
		*length += 1;
		while (s[*length] != '"' && s[*length + 1])
			*length += 1;
	}
	if (s[*length] == '\'')
	{
		*k += 2;
		*length += 1;
		while (s[*length] != '\'' && s[*length + 1])
			*length += 1;
	}
}

static int	ln(char *s)
{
	int	length;
	char c;
	int k;

	c = 32;
	k = 0;
	length = 0;
	while (s[length] && s[length] != c && s[length] != '>' && s[length] != '<')
	{
		skip_quotes(s, &length, &k);
		length++;
	}
	if ((s[length] == '<' || s[length] == '>') && length == 0)
	{
		length++;
		if (s[length] == '<' || s[length] == '>')
			return 2;
		return 1;
	}
	return (length - k);
}

void    ultra_skip_inside_quotes(char *command, int *i)
{
    if (command[*i] == '"')
    {
        *i += 1;
        while(command[*i] != '"')
            *i += 1;
        *i += 1;
    }
    else if (command[*i] == '\'')
    {
        *i += 1;
        while(command[*i] != '\'')
            *i += 1;
        *i += 1;
    }
}

size_t	count_word(char const *str)
{
	int	i;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '|')
	{
		while (str[i] == ' ' && str[i])
			i++;
		ultra_skip_inside_quotes((char *)str, &i);
		if (!str[i])
			break;
		if ((str [i] != '|') && str[i])
			k++;
		while (str[i] != ' ' && str[i] && str[i] != '|')
		{
			ultra_skip_inside_quotes((char *)str, &i);
			if ((str[i] == '<' || str[i] =='>') && str[i] && i != 0 && (str[i - 1] != ' '))
			{
				while(str[i] == '<' || str[i] == '>')
					i++;
				k++;
			}
			else if ((str[i] == '<' || str[i] =='>') && str[i] && i != 0 && (str[i + 1] != ' '))
			{
				while(str[i] == '<' || str[i] == '>')
					i++;
				k++;
			}
			i++;
		}
	}
	return (k);
}
int check_alloc(char **arr, int j)
{
	if (!arr[j])
	{
		ft_print("Error : allocation in split\n", 0);
		while (j >= 0)
		free(arr[j--]);
		free(arr);
		return 1;
	}
	return 0;
}

int skip_space(char *s, int *i)
{
	while (s[*i] < 33)
			*i += 1;
	if (!s[*i])
		return 1;
	return 0;
}
void skip_quotes_copy(char *s, char **arr, int *i, int *k, int j)
{
	char c;

	if (s[*i] == '"' || s[*i] == '\'')
	{
		c = s[*i];
		*i += 1;
		while (s[*i] != c)
		{
			arr[j][*k] = s[*i];
			*i += 1;
			*k += 1;
		}
		*i += 1;
	}
	else
	{
		skip_space(s,i);
		arr[j][*k] = s[*i];
		*i += 1;
		*k += 1;
	}
}


char	**ft_ultra_split(char *s, int	i, int		j,char ** envp)
{
	int		words;
	int		k;
	int		w_len;
	char	**arr;
	
	if (!s)
		return (NULL);
	j = 0;
	words = count_word(s);
	arr = malloc ((words + 1) * sizeof(char *));
	if (!arr)
		return (ft_print("Error : allocation in split\n", 0), NULL);
	while(j < words)
	{
		if (skip_space(s, &i))
			break;
		w_len = ln(&s[i]);
		if (w_len == 0)
		{
			arr[j++] = ft_strdup("''");
			if (skip_space(s, &i))
				break;
			w_len = ln(&s[i]);
		}
		arr[j] = malloc(w_len + 1);
		if (check_alloc(arr, j))
		return (NULL);
		k = 0;
		while (k < w_len)
			skip_quotes_copy(s, arr, &i, &k, j);
		arr[j++][k] = 0;
	}
	arr[j] = NULL;
	arr = dirham(arr, envp);
	// arr = wildcart(arr, envp);
	return (arr);
}
// int main ()
// {
// 	char **str = ft_ultra_split("\"ls\" > ls", 0 ,0, NULL);
// 	for (int i = 0; str[i]; i++)
// 		printf("%s\n", str[i]);
// }

/// ERRORS CONDITIONS 

// ==========================

// export VAR=hello	 (clear)

// echo $VAR	hello (clear)

// echo "$VAR"	hello (clear)

// echo '$VAR'	expected-> $VAR   result -> hello

// ================================

// export A=hi B=there	(clear)

// echo $A $B	         (clear)

// echo "$A-$B"	          expected -> hi-there   result -> nothing 

// echo "$A $B"            expected -> hi there   result -> hi

// =================================

// export NAME=abkaram

// echo "Salam $NAME"        expected -> Salam abkaram     result -> abkaram

// ==================================

// echo "User : $USER, Home : $HOME"

// expected -> User : maen-naj, Home : /home/maen-naj

// result -> empty

// ===================================

// echo $$

// expected ->   pid of minishell 

// result -> empty 

// ===================================

// echo $0

// expected -> bash

// result -> empty

// ====================================

// echo $? 

// expected -> exit status of last command (127 or 0)

// result -> empty

// =================================

// export VAR=value

// echo "$VARabc"        (clear)

// echo "${VAR}abc"   expected -> valueabc    result -> empty

// ==========================================

