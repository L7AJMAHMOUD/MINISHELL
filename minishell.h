/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:20:24 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/22 13:57:12 by abkaram          ###   ########.fr       */
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
    char **command;
	int pipe;
	int and;
	int or;
    struct s_node *next;
}   t_node;

void    read_input();
char	**ft_ultra_split(char *s);
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

/* **************************************************************** */
/*								    */
/*	                     command_tokenization_utils	                */
/*								    */
/* **************************************************************** */

t_node    *command_tokenization(char *command);



void	exe(char **command, char **envp);

#endif