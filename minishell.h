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
	int		k;
	int		nbr;
}	t_command;

typedef struct s_node
{
	char			**command;
	t_command		*arr;
	int				i;
	int				pipe;
	int				hd;
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
t_command	*ft_ultr_split(char *str, char **envp, int q, t_data *data);
void		invalid_param(void);

/* ────────────────────────────── */
/*       ✂️ STRING UTILITIES      */
/* ────────────────────────────── */

char		*ft_strstr(char *haystack, char *needle, size_t i, size_t j);
size_t		ft_strlen(const char *s);
char		*ft_strdup(char *src);
char		**read_stock(char **envp, t_data *data, int j, int i);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char *s1, char *s2);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
char		**ft_split(char const *s, char c);
int			ft_strt(char *haystack, char *needle, size_t i, size_t j);
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
void		echo(char **str, t_data *data, int p);
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
char		**add_to_envp(char **envp, char *ligne, int p, char **str);
void		heredoc_child_cleanup(char **limiters, char *file, char *com);
int			redirect_output_fd(char **command, t_command *arr,
				t_data *data, int i);
int			redirect_input_fd(char **command, t_command *arr,
				t_data *data, int i);

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

t_command	cooking(char *str, int p, int x, t_data *data);
char		**clean_command(char **coammand, t_command *arr);
int			is_redirection(char *command);
int			append_to_fd(char **command, t_command *arr, t_data *data, int i);
char		*ft_strjoin_(char *s1, char *s2);
char		*get_variable(char *str, char **envp, t_data *data);
char		*here_doc_data(char *full_path);
char		*join_strings(char *s1, char *s2);
int			wait_for_child(pid_t pid, t_data *data);
int			strlen_until_special(char *str);
char		*ft_strncpy(char *dst, const char *src, size_t n);
char		*expand_str(char *cmd, char **envp, t_data *data, t_indexes indx);
char		*strmerge_and_free(char *s1, char *s2);
int			count_word(char *s, char c);
int			redirect_parse_double(char *cmd);
void		print_err(t_command *arr, int i);
int			envp_array_length(char **envp);
int			duplicate_line_to_array(char **str, char *ligne, t_indexes *indx);
char		*dup_env_line(char *line);
char		*command_analyse(char *command, char **envp, t_data *data);
char		**arr_sorted(char **str);
void		ft_swap_str(char **s1, char **s2);
char		**copy_envp(char **envp);
void		handle_dollar(t_command *arr, int i, int j, t_data *data);
t_command	*cleaning(char *str, int p, t_command *arr, t_indexes indx);
int			allocate_next_command(t_command *arr, char *str, int *k, int j);
int			handle_empty_quote_command(t_command *arr, t_indexes *indx,
				char *str);
int			complete_quoted_command(t_command *arr, char *str, t_indexes *ind);
int			is_special_char(char c);
void		remove_positional_parameter(t_command *arr, int i, int *p, int j);
void		expand_exit_status(t_command *arr, int i, int *j, int p);
void		expand_env_variable(t_command *arr, t_indexes indx, int *j,
				t_data *data);
void		print_env(char **envp, char **command, t_data *data);
void		minishell(char **str, t_data *data);
void		ft_exit(char ***envp, t_node *node, t_data *data);
int			check_command(char **str, char ***envp, t_node *node, t_data *data);
int			wait_for_child(pid_t pid, t_data *data);
int			check_if_directory(char *path);
int			check_path_directory_or_missing(char *path);
int			check_invalid_path_or_command(char *path);
char		*strjoin_with_slash(char *s1, char *s2);
int			find_path_index(char **envp);
char		*ft_strchr(const char *str, int c);
char		*print_no_such_file_error(char *path);
char		*find_executable_in_path(char **envp, t_data *data, char *path,
				int *j);
char		*print_permission_denied_error(char *path);
char		*print_command_not_found_error(char *path);
char		*print_access_error(char *path);
char		*strdup_until_char(const char *src, int c, int *i);
void		init_fds(int *fds);
void		wait_and_update_status(t_data *data);
char		**get_delimiters(t_command *arr, char **str);
void		process_here_doc(t_data *data, char *file, char **limiters,
				int expand);
int			new_cmd_size(char **command, t_command *arr);
int			is_redirect(char *command);
void		reset_node_flags(t_node *node);
void		rev_(char *s);
void		preparation(char **s, int i);
int			count_words(char *s, char sep, int i, int count);
int			initialisation(t_command *arr, int word);
int			is_empty(char *cmd, int c, int i);
void		print_is_a_directory_error(char *path);

#endif