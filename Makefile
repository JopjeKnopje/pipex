# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jboeve <jboeve@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 12:05:02 by jboeve        #+#    #+#                  #
#    Updated: 2023/05/10 11:52:49 by jboeve        ########   odam.nl          #
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
	   parser.c \
	   commands.c \
	   free.c \
	   error.c \
	   processes.c \
	   meuk.c

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

.PHONY: make_libft

all: make_libft $(NAME) test_exec

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(INC) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

test_exec: test_exec.c $(LIBFT)
	gcc test_exec.c $(INC) $(FLAGS) $(LIBFT) -o test_exec 


make_libft:
	$(MAKE) -C libft

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean dfclean all

run: all
	@# ./$(NAME) input_file.txt "test_exec 1" "prog2 1" "prog3 1" output_file.txt
	@# ./$(NAME) input_file.txt /bin/ls cat output_file.txt
	@# ./$(NAME) input_file.txt ls cat output_file.txt
	@# ./$(NAME) input_file.txt "./bin/ls -la" cat output_file.txt
	@# ./$(NAME) input_file.txt "/bin/ls -la" cat output_file.txt
	@# ./$(NAME) input_file.txt "ls -la" cat output_file.txt
	@# ./$(NAME) input_file.txt "./test_exec" cat output_file.txt
	@# ./$(NAME) input_file.txt "./test_exec 1" "./test_exec 1" output_file.txt

compile_commands: dfclean fclean
	$(MAKE) | compiledb

dfclean:
	$(MAKE) -C libft fclean
dre:
	$(MAKE) -C libft re

mem:
	memdetect/memdetect.sh . $(CFLAGS) $(INC) -e test_exec --args "input_file.txt" "/bin/ls" "cat" "output_file.txt"

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $(INC) $(TEST_INC) $< $(OBJS) $(TESTS_UTILS) $(LIBFT) -o $@ -lcriterion 

.PHONY: build_test
build_test: $(LIBFT) $(OBJS) $(TEST_BINS)
	# @for test in $(TEST_BINS) ; do ./$$test -j4; done

test:
	$(MAKE) clean
	$(MAKE) build_test TEST_BUILD=1make
