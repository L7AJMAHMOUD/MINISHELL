/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abkaram <abkaram@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/18 11:20:24 by maen-naj		  #+#	#+#			 */
/*   Updated: 2025/05/05 08:51:30 by abkaram		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
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

void	read_input();
char	**ft_ultra_split(char *s);
void	invalid_param(void);

/* **************************************************************** */
/*									*/
/*						  linked_lists_utils						*/
/*									*/
/* **************************************************************** */
void ft_nodeadd_back(t_node **lst, t_node *new);
void	ft_lstadd_front(t_node **lst, t_node *new);
void	ft_lstadd_back(t_node **lst, t_node *new);
int ft_lstsize(t_node *lst);
void delete_node(t_node **head);;

/* **************************************************************** */
/*									*/
/*							   strings_utils						*/
/*									*/
/* **************************************************************** */

char	*ft_strstr(char *haystack, char *needle);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *src );
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int	ft_strt(char *haystack, char *needle);
int	ft_strcmp(char *s1, char *s2);
int	ft_is_spc(int cmd);
int ft_is_spc2(int cmd);

/* **************************************************************** */
/*									*/
/*						 command_tokenization_utils					*/
/*									*/
/* **************************************************************** */
void	command_tokenization(t_node **node, char *command);
void node_null(t_node *node);
void free_all_ul_split(char **str);

/* **************************************************************** */
/*									*/
/*								 commands   						*/
/*									*/
/* **************************************************************** */

void	pwd(char **envp);
void	echo(char **str, int fd);




void	ft_print(char *s, int i);
void	exe(char **command, char **envp);

int   and(char *command, int i, int k);
void	check_and_last(char *command);
int		or(char *command, int i, int k);
int		pipe_detector(char *command);
void	and_single_operator(char *command, int *i);
void	or_single_operator(char *command, int *i);
void	check_or_last(char *command);
void	skip_inside_quotes(char *command, int *i);
int	command_analyze(char *command);
int		parenth(char *command);

#endif