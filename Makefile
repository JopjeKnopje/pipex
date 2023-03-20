# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jboeve <jboeve@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 12:05:02 by jboeve        #+#    #+#                  #
#    Updated: 2023/03/20 23:50:53 by joppe         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = libft/build/libft.a

# CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address

INC = -Ilibft/include -Iinclude 

SRC_DIR = src
SRCS = main.c \
	   utils.c \
	   parser.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

HEADER_DIR = include
HEADERS = pipex.h
HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


TEST_DIR = tests
TESTS = test_1.c
TESTS_UTILS = test_push_swap.c
TESTS_UTILS := $(addprefix $(TEST_DIR)/, $(TESTS_UTILS))
TESTS := $(addprefix $(TEST_DIR)/, $(TESTS))
TEST_INC = -I/Users/jboeve/homebrew/include -L/Users/jboeve/homebrew/lib
TEST_BIN_DIR = bin
TEST_BIN_DIR := $(addprefix $(TEST_DIR)/, $(TEST_BIN_DIR))
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/bin/%, $(TESTS))

ifdef TEST_BUILD
CFLAGS += -DBUILD_TESTER
endif


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(INC) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: $(LIBFT)
$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean dfclean all

run: all
	# ./$(NAME) "ls -lsa" "echo blabla > test_file" "cat test_file" "neofetch"
	# ./$(NAME) "echo blabla > test_file"
	./$(NAME) input_file.txt output_file.txt


compile_commands: dfclean fclean
	$(MAKE) | compiledb

dfclean:
	$(MAKE) -C libft fclean
dre:
	$(MAKE) -C libft re

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $(INC) $(TEST_INC) $< $(OBJS) $(TESTS_UTILS) $(LIBFT) -o $@ -lcriterion 

.PHONY: build_test
build_test: $(LIBFT) $(OBJS) $(TEST_BINS)
	# @for test in $(TEST_BINS) ; do ./$$test -j4; done

test:
	$(MAKE) clean
	$(MAKE) build_test TEST_BUILD=1make
