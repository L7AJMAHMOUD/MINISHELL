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
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 100000

typedef struct s_node
{
	char **command;
	int pipe;
	int and;
	int or;
	struct s_node *next;
}   t_node;

void    read_input(char ***envp);
char	**ft_ultra_split(char *s, int	i, int		j, char **envp);
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
char **read_stock(char **envp);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int	ft_isdigit(int c);
char	**ft_split(char const *s, char c);
int	ft_strt(char *haystack, char *needle);
int	ft_strcmp(char *s1, char *s2);
int	ft_is_spc(int cmd);
int is_something(int cmd);

/* **************************************************************** */
/*									*/
/*						 command_tokenization_utils					*/
/*									*/
/* **************************************************************** */
void	command_tokenization(t_node **node, char *command, char **envp);
void node_null(t_node *node);
void free_all_ul_split(char **str);

/* **************************************************************** */
/*									*/
/*								 commands   						*/
/*									*/
/* **************************************************************** */

void	pwd(int i);
void echo(char **str, int fd, char **envp);
void cd(char ***envp, char *arg);
void export(char ***envp, char **command);
void unset(char ***envp, char **command);

char	*ft_shearch(char *haystack, char *needle);

void baner();

void	ft_print(char *s, int i);
void	exe(char **command, char **envp, t_node *node);
char	*find_path(char *path, char **envp);

int   	and(char *command, int i, int k);
int		redirect_parse(char *command);
void	check_and_last(char *command);
int		or(char *command, int i, int k);
int		pipe_detector(char *command);
void	and_single_operator(char *command, int *i);
void	or_single_operator(char *command, int *i);
void	check_or_last(char *command);
void	skip_inside_quotes(char *command, int *i);
int		command_analyze(char *command);
int		parenth(char *command);
char	*ft_strstr_pare(char *command);
int ultra_redirect_parse(char *command);
int ultra_redirect_parsee(char *command);
void	apply_redirections(char **command);
int	ft_str_cmp(char *s1, char *s2);
int check_command(char **str, char ***envp, t_node *node);
void free_all_node(t_node *node);
int pip(t_node *node, char ***envp);
char **add_to_envp(char **envp, char *ligne, int i);
char **dirham(char **str, char **envp);
void redirect_output_fd(char **command);
void redirect_input_fd(char **command);
char **wildcart(char **st, char **envp);
void    bash_sig_handler(int sig);
void	cmd_final(char **command, int i);
void shy_emoji_banner();
#endif