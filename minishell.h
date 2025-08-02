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
# define MINISHELL_H

/* ────────────────────────────── */
/*           🧠 HEADERS           */
/* ────────────────────────────── */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

/* ────────────────────────────── */
/*         ⚙️ DEFINITIONS         */
/* ────────────────────────────── */
# define SPACE_CHAR ' '
# define PIPE_CHAR '|'
# define REDIRECT_IN '<'
# define REDIRECT_OUT '>'
# define QUOTE_DOUBLE '"'
# define QUOTE_SINGLE '\''
# define BUFFER_SIZE 100000

extern int	g_hsig;

/* ────────────────────────────── */
/*         📦 STRUCTURES          */
/* ────────────────────────────── */

typedef struct s_data
{
	char	*command;
	char	*pwd;
	char	***envp;
	char	*path;
	int		*pid;
	char	*com;
	char	*file;
	char	**limiters;
	int		fd;
	int		id;
	int		i;
	int		status;
}	t_data;

typedef struct s_command
{
	char	*command;
	char	**envp;
	t_data	*data;
	int		q;
	int		nbr;
}	t_command;

typedef struct s_node
{
	char			**command;
	t_command		*arr;
	int				i;
	int				pipe;
	int				and;
	int				hd;
	int				or;
	struct s_node	*next;
}	t_node;

typedef struct s_indexes
{
	int	i;
	int	j;
	int	k;
	int	p;
	int	c;
	int	m;
}	t_indexes;

/* ────────────────────────────── */
/*        🔧 CORE FUNCTIONS       */
/* ────────────────────────────── */

int			ft_atoi(const char *str);
void		free_arr(t_command *arr, int i);
void		read_input(char ***envp, t_data *data);
char		**ft_ultra_split(char *s, char **envp, t_data *data);
t_command	*ft_ultr_split(char *str, char **envp, int e, t_data *data);
void		invalid_param(void);

/* ────────────────────────────── */
/*       ✂️ STRING UTILITIES      */
/* ────────────────────────────── */

char		*ft_strstr(char *haystack, char *needle);
size_t		ft_strlen(const char *s);
char		*ft_strdup(char *src );
char		**read_stock(char **envp, t_data *data);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char *s1, char *s2);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
char		**ft_split(char const *s, char c);
int			ft_strt(char *haystack, char *needle);
int			ft_strcmp(char *s1, char *s2);
int			is_something(char *cmd);

/* ────────────────────────────── */
/*       🧩 PARSING & TOKENS      */
/* ────────────────────────────── */

void		command_tokenization(t_node **node, char *command,
				char **envp, t_data *data);
void		free_all_ul_split(char **str);
char		*ft_itoa(int n);
int			validate_pipe_syntax(char *command);

/* ────────────────────────────── */
/*        💻 BUILTIN CMDS         */
/* ────────────────────────────── */

void		pwd(t_data *data);
void		echo(char **str, t_data *data);
void		cd(char ***envp, char **arg, t_data *data);
void		export(char ***envp, char **command, t_data *data);
void		unset(char ***envp, char **command, t_data *data);
int			find_env_var_index(char **envp, char *ligne, int *k);
int			is_prefix_equal_until_equal_sign(char *s1, char *s2);
char		**apply_redirections(t_node *node, char ***envp,
				t_data *data, t_indexes indx);
void		ft_print(char *s, int i);
void		exe(char **envp, t_node *node, t_data *data);
char		*find_path(char *path, char **envp, t_data *data);
int			redirect_parse(char *command);
int			pipe_detector(char *command);
void		skip_inside_quotes(char *command, int *i);
int			command_analyze(char *command, t_data *data);
int			here_doc(t_node *node, char **envp, t_data *data);
int			strcmp_until_equal(char *s1, char *s2);
int			check_command(char **str, char ***envp, t_node *node, t_data *data);
void		free_all_node(t_node *node);
int			pip(char ***envp, t_data *data, t_node *cur);
char		**add_to_envp(char **envp, char *ligne, int i);
void		heredoc_child_cleanup(char **limiters, char *file, char *com);
int			redirect_output_fd(char **command, t_command *arr, t_data *data);
int			redirect_input_fd(char **command, t_data *data);

/* ────────────────────────────── */
/*       ⚡ SIGNAL HANDLING        */
/* ────────────────────────────── */

void		bash_sig_handler(int signum);
void		signal_init(t_data *data);
void		signal_init_here(t_data *data);
void		heredoc_sigint_handler(int sig);

/* ────────────────────────────── */
/*        ♻️ FD / MEM CLEANUP     */
/* ────────────────────────────── */

void		*ft_memset(void *b, int c, size_t len);
void		cleanup_fds(void);

/* ────────────────────────────── */
/*      🍜 COMMAND UTILITIES      */
/* ────────────────────────────── */

t_command	cooking(char *str, char **envp, int p, int x, t_data *data);
char		**clean_command(char **coammand, t_command *arr);
int			is_redirection(char *command);
int			append_to_fd(char **command, t_command *arr, t_data *data);
char		*ft_strjoin_(char *s1, char *s2);
char		*get_variable(char *str, char **envp, t_data *data);
char		*here_doc_data(void);
char		*join_strings(char *s1, char *s2);
int			wait_for_child(pid_t pid, t_data *data);
int			strlen_(char *str);
char		*ft_strncpy(char *dst, const char *src, size_t n);
char		*expand_str(char *cmd, char **envp, t_data *data);
char		*strmerge_and_free(char *s1, char *s2);

#endif