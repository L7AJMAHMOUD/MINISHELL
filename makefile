NAME    = minishell
CC      = cc
FLAGS   = -Wall -Wextra -Werror -g3
RM      = rm -f

HEAD    = minishell.h

SRC_DIRS = src/builtins \
           src/execution \
           src/parsing \
           src/heredoc \
           src/signals \
           src/core \
           src/utils

SRCS = main.c $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

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

re: fclean all

run: $(NAME)
	@./$(NAME)

.PHONY: all clean fclean re run
