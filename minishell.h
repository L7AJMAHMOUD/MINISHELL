/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:20:24 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/21 15:17:23 by maen-naj         ###   ########.fr       */
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
    char *token;
    struct s_node *next;
}   t_node;

void    read_input();
char	**ft_split(char const *s, char c);
void    invalid_param(void);

/* **************************************************************** */
/*								    */
/*	                      linked_lists_utils	                    */
/*								    */
/* **************************************************************** */

void ft_nodeadd_back(t_node **lst, t_node *new);
void ft_lstadd_front(t_node **lst, t_node *new);
int ft_lstsize(t_node *lst);
void delete_node(t_node **head);
t_node	*create_node(char *data);
void	print_list(t_node *head);

/* **************************************************************** */
/*								    */
/*	                           strings_utils	                    */
/*								    */
/* **************************************************************** */

char	*ft_strstr(char *haystack, char *needle);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *src );
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	**free_split(char **tab);

/* **************************************************************** */
/*								    */
/*	                     command_tokenization_utils	                */
/*								    */
/* **************************************************************** */

t_node    *command_tokenization(char *command);
int    command_analyze(char *command);

#endif