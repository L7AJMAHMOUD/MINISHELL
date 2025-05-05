NAME = minishell
CC = cc
FLAGS = #-Wall -Wextra -Werror 
HEAD = minishell.h
RM = rm -f
SRCS = $(wildcard *.c)

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