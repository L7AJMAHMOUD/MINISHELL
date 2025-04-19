/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:20:24 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/19 19:00:39 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_node
{
    char *command;
    char *flags;
    char *arg;
	int pipe;
    int flag;
	int and;
	int or;
    struct s_node *next;
}   t_node;

void    read_input();
t_node	*create_node(char *data);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void    invalid_param(void);

char	*ft_strstr(char *haystack, char *needle);

#endif