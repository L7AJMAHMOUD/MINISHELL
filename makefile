NAME := minishell
CC := cc
CPPFLAGS ?=
CFLAGS ?= -Wall -Wextra -Werror -g
LDFLAGS ?=
LDLIBS ?= -lreadline
BUILD_DIR ?= build
PYTHON ?= python3

SRCS := main.c $(sort $(wildcard src/*/*.c))
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME) minishell-sanitize

re:
	$(MAKE) fclean
	$(MAKE) all

test: $(NAME)
	$(PYTHON) tests/test_shell.py ./$(NAME)

format:
	clang-format -i $(SRCS) minishell.h

sanitize:
	$(MAKE) NAME=minishell-sanitize BUILD_DIR=build/sanitize CC=clang CFLAGS='-Wall -Wextra -Werror -g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer' LDFLAGS='-fsanitize=address,undefined' all
	ASAN_OPTIONS=detect_leaks=1 $(PYTHON) tests/test_shell.py ./minishell-sanitize

-include $(DEPS)
.PHONY: all clean fclean re test sanitize format
