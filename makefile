NAME = minishell
CC = cc
FLAGS = #-Wall -Wextra -Werror 
HEAD = minishell.h
RM = rm -f
SRCS = main.c read_input.c linked_lists_utils.c ft_split.c split_utils.c handle_errors.c utils.c command_tokenization.c exe.c or.c and.c pipe.c analyze_command.c

OBJ = $(SRCS:.c=.o)



all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -lreadline -o $(NAME)


%.o : %.c $(HEAD)
	@$(CC) $(FLAGS) -c $< -o $@

clean : 
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

run:	$(NAME)
	@./$(NAME)

.PHONY : all clean fclean re