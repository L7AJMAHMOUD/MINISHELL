#ifndef MINISHELL_H
#define MINISHELL_H

/* Headers */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Definitions */
#define SPACE_CHAR ' '
#define PIPE_CHAR '|'
#define REDIRECT_IN '<'
#define REDIRECT_OUT '>'
#define QUOTE_DOUBLE '"'
#define QUOTE_SINGLE '\''
#define BUFFER_SIZE 100000

/* Structures */

typedef struct s_data
{
    char *pwd;
    char ***envp;
    char *path;
    int *pid;
    int id;
    int status;
    int interactive;
} t_data;

typedef struct s_command
{
    char *command;
    int ex; /* -1 when a redirection expands to zero or multiple fields. */
    int q;  /* Nonzero for words; zero for redirection operators. */
    int k;  /* Whether the token contains quoted text. */
} t_command;

typedef struct s_node
{
    char **command;
    t_command *arr;
    int i;
    int hd;
    struct s_node *next;
} t_node;

typedef struct s_indexes
{
    int i;
    int j;
    int k;
    int p;
    int c;
    int m;
} t_indexes;

/* Core Functions */

void free_arr(t_command *arr, int i);
char *read_shell_line(t_data *data, const char *prompt);
void read_input(char ***envp, t_data *data);

/* String Utilities */

size_t ft_strlen(const char *s);
char *ft_strdup(char *src);
char **read_stock(char **envp, t_data *data, int j, int i);

int ft_isalpha(int c);
int ft_isalnum(int c);

int ft_strcmp(char *s1, char *s2);

int ft_strncmp(char *s1, char *s2, size_t n);

/* Parsing & Tokens */

void command_tokenization(t_node **node, char *command, char **envp, t_data *data);
void free_all_ul_split(char **str);

int validate_pipe_syntax(char *command);

/* Builtin Cmds */

void pwd(t_data *data);
void echo(char **str, t_data *data, int p);
void cd(char ***envp, char **arg, t_data *data);
void export(char ***envp, char **command, t_data *data);
void unset(char ***envp, char **command, t_data *data);
int find_env_var_index(char **envp, char *ligne, int *k);
int is_prefix_equal_until_equal_sign(char *s1, char *s2);
char **apply_redirections(t_node *node, char ***envp, t_data *data);
void ft_print(char *s, int i);
void execute_external(t_node *node, char **envp, t_data *data);
int shell_wait_status(int status);
void exe(char **envp, t_node *node, t_data *data);

int redirect_parse(char *command);
int pipe_detector(char *command);
void skip_inside_quotes(char *command, int *i);
int command_analyze(char *command, t_data *data);
int prepare_heredocs(t_node *node, t_data *data);

int strcmp_until_equal(char *s1, char *s2);
int check_command(char **str, char ***envp, t_node *node, t_data *data);
void free_all_node(t_node *node);
int pip(char ***envp, t_data *data, t_node *cur);
char **add_to_envp(char **envp, char *ligne, int p, char **str);

int redirect_output_fd(char **command, t_command *arr, t_data *data, int i);
int redirect_input_fd(char **command, t_command *arr, t_data *data, int i);

/* Signal Handling */

void bash_sig_handler(int signum);
void signal_init(t_data *data);

/* Command Utilities */

char **clean_command(char **coammand, t_command *arr);

int append_to_fd(char **command, t_command *arr, t_data *data, int i);

char *get_variable(char *str, char **envp, t_data *data);

char *join_strings(char *s1, char *s2);
int max_pipe_detector(char *command);
int wait_for_child(pid_t pid, t_data *data);
int strlen_until_special(char *str);

char *expand_str(char *cmd, char **envp, t_data *data);
char *strmerge_and_free(char *s1, char *s2);

int redirect_parse_double(char *cmd);
void print_err(t_command *arr, int i);
int envp_array_length(char **envp);
int duplicate_line_to_array(char **str, char *ligne, t_indexes *indx);
char *dup_env_line(char *line);
char *command_analyse(char *command, char **envp, t_data *data);
char **arr_sorted(char **str);
void ft_swap_str(char **s1, char **s2);
char **copy_envp(char **envp);

void print_env(char **envp, char **command, t_data *data);

void ft_exit(char ***envp, t_node *node, t_data *data);

char *ft_strchr(const char *str, int c);

int new_cmd_size(char **command, t_command *arr);
int is_redirect(char *command);

void init_autosuggestions(void);

#endif
