NAME    = minishell
CC      = cc
# FLAGS   = -Wall -Wextra -Werror -g3
RM      = rm -f
HEAD    = minishell.h

SRCS = main.c \
       src/builtins/cd.c \
       src/builtins/commands.c \
       src/builtins/export.c \
       src/builtins/utils_export.c \
       src/builtins/helpr_export.c \
       src/builtins/pseudo_export.c \
       src/builtins/unset.c \
       src/execution/exe.c \
       src/execution/pseudo_exe.c \
       src/execution/helpr_exe.c \
       src/execution/utils_exe.c \
       src/execution/pipe.c \
       src/execution/utils_pipe.c \
       src/execution/pipe_detec.c \
       src/execution/pipe_syn.c \
       src/execution/output_redirection.c \
       src/execution/input_redirection.c \
       src/execution/append_redirection.c \
       src/execution/redirections_applications.c \
       src/core/read_input.c \
       src/core/utils_read_input.c \
       src/core/cooking.c \
       src/core/utils_cooking.c \
       src/core/helpr_cooking.c \
       src/core/pseudo_cooking.c \
       src/core/pre_cooking.c \
       src/core/analyze_command.c \
       src/parsing/redirections.c \
       src/parsing/parse.c \
       src/parsing/expand.c \
       src/parsing/command_tokenization.c \
       src/parsing/utils_cmd_token.c \
       src/parsing/split.c \
       src/parsing/split_utils.c \
       src/parsing/ft_ultra_split.c \
       src/parsing/utils_ft_ultra_split.c \
       src/parsing/cleaning_command.c \
       src/parsing/utils_cleaning_command.c \
       src/parsing/handle_errors.c \
       src/heredoc/here_document.c \
       src/heredoc/utils_here_document.c \
       src/heredoc/helpr_here_document.c \
       src/heredoc/herdoc_data.c \
       src/signals/bash_signals.c \
       src/utils/utils.c \
       src/utils/utils_utils.c \
       src/utils/ft_itoa.c \
       src/utils/ft_print.c \
       src/utils/libft.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo "\033[1;32m[OK]\033[0m Compiled $(NAME)"

%.o: %.c $(HEAD)
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean 