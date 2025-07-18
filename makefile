# # ╔═══════════════════════════════════════════╗
# # ║        MINISHELL OF NIGHTMARES           ║
# # ╚═══════════════════════════════════════════╝

# NAME        = minishell
# CC          = cc
# FLAGS       = #-Wall -Wextra -Werror
# HEAD        = minishell.h
# RM          = rm -f
# SRCS        = $(wildcard *.c)
# OBJ         = $(SRCS:.c=.o)

# RED         = \033[1;31m
# DARK_RED    = \033[38;5;88m
# DRIP        = \033[38;5;52m
# RESET       = \033[0m

# CURSED_MSG1 = "$(RED)⚰️  Summoning the spirits of your code...$(RESET)"
# CURSED_MSG2 = "$(RED)🔪  Carving your objects into existence...$(RESET)"
# CURSED_MSG3 = "$(RED)👻  Haunting your terminal with minishell...$(RESET)"
# CURSED_MSG4 = "$(RED)🦇  The darkness of compilation is complete...$(RESET)"
# CURSED_MSG5 = "$(RED)💉  Injecting life into the shell...$(RESET)"
# CURSED_MSG6 = "$(RED)🩸  Cleaning away the blood stains...$(RESET)"
# CURSED_MSG7 = "$(RED)⚱️  Your remnants have been buried...$(RESET)"

# all: horror_banner $(NAME)

# horror_banner:
# 	@echo "$(RED)"
# 	@echo "    ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗"
# 	@echo "    ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║"
# 	@echo "    ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║"
# 	@echo "    ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║"
# 	@echo "    ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
# 	@echo "    ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
# 	@echo "$(DARK_RED)"
# 	@echo "             💀 THE SHELL FROM YOUR NIGHTMARES 💀"
# 	@echo "$(RESET)"
# 	@echo "$(DRIP)          .         .         .         .         ."
# 	@echo "          │         │         │         │         │"
# 	@echo "$(RESET)"

# $(NAME): $(OBJ)
# 	@echo $(CURSED_MSG1)
# 	@sleep 0.5
# 	@echo $(CURSED_MSG2)
# 	@sleep 0.5
# 	@$(CC) $(OBJ) -lreadline -o $(NAME)
# 	@echo $(CURSED_MSG4)
# 	@sleep 0.5
# 	@echo "$(RED)☠️  $(NAME) has been conjured from the abyss...$(RESET)"

# %.o: %.c $(HEAD)
# 	@echo "$(RED)↯ Sacrificing: $<$(RESET)"
# 	@$(CC) $(FLAGS) -c $< -o $@

# clean:
# 	@echo $(CURSED_MSG6)
# 	@$(RM) $(OBJ)
# 	@echo "$(DARK_RED)The evidence has been destroyed...$(RESET)"

# fclean: clean
# 	@echo $(CURSED_MSG7)
# 	@$(RM) $(NAME)
# 	@echo "$(DARK_RED)All traces of $(NAME) have been exorcised from this realm...$(RESET)"

# re: fclean all

# run: $(NAME)
# 	@echo $(CURSED_MSG5)
# 	@echo "$(RED)🧟 Resurrecting shell from the dead...$(RESET)"
# 	@./$(NAME)

# leak: $(NAME)
# 	@echo "$(RED)🧪 Testing for blood leaks...$(RESET)"
# 	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# .PHONY: all clean fclean re run leak horror_banner


NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
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

# NAME = minishell
# CC = cc
# FLAGS = 
# HEAD = minishell.h
# RM = rm -f
# SRCS = $(wildcard *.c)
# OBJ = $(SRCS:.c=.o)

# READLINE_INCLUDE = -I$(shell brew --prefix readline)/include
# READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

# all: $(NAME)

# $(NAME): $(OBJ)
# 	@$(CC) $(OBJ) $(READLINE_INCLUDE) $(READLINE_LIB) -o $(NAME)

# %.o: %.c $(HEAD)
# 	@$(CC) $(FLAGS) $(READLINE_INCLUDE) -c $< -o $@

# clean:
# 	$(RM) $(OBJ)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

# run: $(NAME)
# 	@./$(NAME)

# .PHONY: all clean fclean re run