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
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * DÉFINITIONS ET CONSTANTES
 */
#define SPACE_CHAR ' '
#define PIPE_CHAR '|'
#define REDIRECT_IN '<'
#define REDIRECT_OUT '>'
#define QUOTE_DOUBLE '"'
#define QUOTE_SINGLE '\''
#define false 0
#define true 1
#define BUFFER_SIZE 100000

typedef struct s_data
{
	char *command;
	char *pwd;
	char *path;
	int status;
}   t_data;
typedef struct s_command
{
	char *command;
	char **envp;
	t_data *data;
	int q;
	int nbr;
}   t_command;

typedef struct s_node
{
	char **command;
	t_command *arr;
	int i;
	int pipe;
	int and;
	int or;
	struct s_node *next;
}   t_node;

int	ft_atoi(const char *str);

void    read_input(char ***envp, t_data *data);
char	**ft_ultra_split(char *s, char **envp, t_data *data);
t_command *ft_ultr_split(char *str, char ** envp, int *words, int e, t_data *data);
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
char    *strjoin(char *s1, char *s2);

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
void	command_tokenization(t_node **node, char *command, char **envp, t_data *data);
void node_null(t_node *node);
void free_all_ul_split(char **str);
char	*ft_itoa(int n);
int validate_pipe_syntax(char *command);

/* **************************************************************** */
/*									*/
/*								 commands   						*/
/*									*/
/* **************************************************************** */

void	pwd(t_data *data);
void echo(char **str, t_data *data);
void cd(char ***envp, char **arg, t_data *data);
void export(char ***envp, char **command, t_data *data);
void unset(char ***envp, char **command, t_data *data);

char	*ft_shearch(char *haystack, char *needle);

void baner();
void    ultra_skip_inside_quotes(char *command, int *i);
void	ft_print(char *s, int i);
void	exe(char **envp, t_node *node, t_data *data);
char *find_path(char *path, char **envp, t_data *data);
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
char ** apply_redirections(char **command, t_command *arr, char **envp, t_data *data);
int	ft_str_cmp(char *s1, char *s2);
int check_command(char **str, char ***envp, t_node *node, t_data *data);
void free_all_node(t_node *node);
int pip(t_node *node, char ***envp, t_data *data);
char **add_to_envp(char **envp, char *ligne, int i);
char **dirham(char **str, char **envp);
void  redirect_output_fd(char **command);
void redirect_input_fd(char **command);
char **wildcart(char **st, char **envp);
void    bash_sig_handler(int sig);
void	*ft_memset(void *b, int c, size_t len);
void	cmd_final(char ***command);
void shy_emoji_banner();
t_command cooking(char *str, char **envp, int p, int x, t_data *data);
void	list(char **command);
char **clean_command(char **coammand, t_command *arr);
int 	is_redirection(char *command);
void append_to_fd(char **command);
void	here_doc(char **command, t_command *arr, char **envp, t_data *data);
char	*ft_strjoin_(char *s1, char *s2);
char* get_variable(char *str, char **envp);
char *	here_doc_data();
#endif
