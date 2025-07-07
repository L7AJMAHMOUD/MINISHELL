/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultra_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/07 14:26:45 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int is_redirect_op(char c)
{
	return (c == REDIRECT_IN || c == REDIRECT_OUT);
}
static int is_quote(char c)
{
	return (c == QUOTE_DOUBLE || c == QUOTE_SINGLE);
}

static int skip_quoted_content(const char *str, int *pos)
{
	if (!str || !pos || !str[*pos])
		return false;
		
	char quote_char = str[*pos];
	if (!is_quote(quote_char))
		return false;
	(*pos)++;
	while (str[*pos] && str[*pos] != quote_char)
		(*pos)++;
		
	if (str[*pos] == quote_char)
	{
		(*pos)++;
		return true;
	}
	return false;
}
static void skip_spaces(const char *str, int *pos)
{
	if (!str || !pos)
		return;
		
	while (str[*pos] && is_space(str[*pos]))
		(*pos)++;
}
static int calculate_word_length(const char *str, int start_pos)
{
	if (!str || !str[start_pos])
		return 0;
		
	int pos = start_pos;
	int length = 0;
	int in_quotes = false;

	if (is_redirect_op(str[pos]))
	{
		length++;
		pos++;
		if (str[pos] && str[pos] == str[pos - 1])
			length++;
		return length;
	}
	while (str[pos] && !is_space(str[pos]) && str[pos] != PIPE_CHAR)
	{
		if (is_quote(str[pos]))
		{
			int old_pos = pos;
			if (skip_quoted_content(str, &pos))
			{
				length += pos - old_pos - 2;
				in_quotes = true;
			}
			else
				return -1;
		}
		else if (is_redirect_op(str[pos]))
			break;
		else
		{
			length++;
			pos++;
		}
	}
		
	return length;
}

static size_t count_words(const char *str)
{
	if (!str)
		return 0;
		
	size_t word_count = 0;
	int pos = 0;
		
	while (str[pos] && str[pos] != PIPE_CHAR)
	{
		skip_spaces(str, &pos);
		
		if (!str[pos] || str[pos] == PIPE_CHAR)
			break;
		word_count++;
		while (str[pos] && !is_space(str[pos]) && str[pos] != PIPE_CHAR)
		{
			if (is_quote(str[pos]))
			{
				if (!skip_quoted_content(str, &pos))
					return 0;
			}
			else if (is_redirect_op(str[pos]))
			{
				if (pos > 0 && !is_space(str[pos - 1]))
					break;
				pos++;
				if (str[pos] && str[pos] == str[pos - 1])
					pos++;
				word_count++;
				break;
			}
			else
				pos++;
		}
	}
		
	return word_count;
}

static int check_allocation(char **arr, int index)
{
	if (!arr[index])
	{
		ft_print("Error: allocation failed in split\n", 0);
		for (int i = 0; i < index; i++)
		{
			if (arr[i])
				free(arr[i]);
		}
		free(arr);
		return false;
	}
	return true;
}

static int copy_word(const char *src, char *dest, int *src_pos, int word_len)
{
	if (!src || !dest || !src_pos)
		return false;
		
	int dest_pos = 0;
	int start_pos = *src_pos;

	if (is_redirect_op(src[*src_pos]))
	{
		dest[dest_pos++] = src[(*src_pos)++];
		if (src[*src_pos] && src[*src_pos] == src[*src_pos - 1])
			dest[dest_pos++] = src[(*src_pos)++];
		dest[dest_pos] = '\0';
		return true;
	}
	while (*src_pos < start_pos + word_len + (word_len > 0 ? 2 : 0) && 
		   src[*src_pos] && 
		   !is_space(src[*src_pos]) && 
		   src[*src_pos] != PIPE_CHAR)
	{
		if (is_quote(src[*src_pos]))
		{
			char quote_char = src[*src_pos];
			(*src_pos)++;
			while (src[*src_pos] && src[*src_pos] != quote_char)
			{
				dest[dest_pos++] = src[(*src_pos)++];
			}
			
			if (src[*src_pos] == quote_char)
				(*src_pos)++;
			else
				return false;
		}
		else if (is_redirect_op(src[*src_pos]))
			break;
		else
			dest[dest_pos++] = src[(*src_pos)++];
	}
		
	dest[dest_pos] = '\0';
	return true;
}

char **ft_ultra_split(char *s, int i, int j, char **envp)
{
	if (!s)
		return NULL;
	size_t word_count = count_words(s);
	if (word_count == 0)
		return NULL;
	char **result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
	{
		ft_print("Error: allocation failed in split\n", 0);
		return NULL;
	}
	i = 0;
	j = 0;
		
	while (j < word_count && s[i])
	{
		skip_spaces(s, &i);
		
		if (!s[i] || s[i] == PIPE_CHAR)
			break;
		int word_len = calculate_word_length(s, i);
		if (word_len < 0)
		{
			ft_print("Error: unclosed quote\n", 0);
			for (int k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return NULL;
		}
		if (word_len == 0)
		{
			if (j == 0)
				result[j] = ft_strdup("''");
			else
				result[j] = ft_strdup("");
			if (!check_allocation(result, j))
				return NULL;
			skip_quoted_content(s, &i);
		}
		else
		{
			result[j] = malloc(word_len + 1);
			if (!check_allocation(result, j))
				return NULL;
			if (!copy_word(s, result[j], &i, word_len))
			{
				ft_print("Error: failed to copy word\n", 0);
				for (int k = 0; k <= j; k++)
					free(result[k]);
				free(result);
				return NULL;
			}
		}
		j++;
	}
	result[j] = NULL;
	result = dirham(result, envp);
	if (!result)
		return NULL;
	return result;
}

// int main ()
// {
// 	char **str = ft_ultra_split("\"ls > ls\"", 0 ,0, NULL);
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

