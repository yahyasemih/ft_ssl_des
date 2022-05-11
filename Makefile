# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 17:48:29 by yez-zain          #+#    #+#              #
#    Updated: 2022/05/11 18:22:25 by yez-zain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC = gcc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
SRCS = ft_ssl.c main.c md5/md5.c base64/base64.c base64/encode.c base64/decode.c\
	utils/commands_utils.c utils/ft_read_block.c utils/libc_utils.c des/des.c\
	sha256/sha256.c md5/state_operations.c md5/string_operations.c\
	utils/swap_bytes.c utils/write_in_hex.c sha256/state_operations.c\
	sha256/string_operations.c sha256/block_operations.c utils/parse_commands.c\
	md5/block_operations.c utils/free_args.c
DEPS = ft_ssl.h md5/md5.h base64/base64.h des/des.h sha256/sha256.h\
	utils/commands_utils.h utils/ft_read_block.h utils/libc_utils.h\
	md5/state_operations.h md5/string_operations.h utils/swap_bytes.h\
	utils/write_in_hex.h sha256/state_operations.h sha256/string_operations.h\
	sha256/block_operations.h md5/block_operations.h
OBJECTS = $(SRCS:.c=.o)
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(RED)Compiling $(NAME)...$(NC)"
	@echo "$(RED)Linking...$(NC)"
	@$(CC) $(FLAGS) $(LDFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)Finished linking && compiling...$(NC)"

%.o: %.c $(DEPS)
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(RED)Compiling $< ...$(NC)"

clean:
	@echo "$(RED)Cleaning objects...$(NC)"
	@rm -rf $(OBJECTS)
	@echo "$(GREEN)Cleaned objects...$(NC)"

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@echo "$(GREEN)Cleaned $(NAME)...$(NC)"

re: fclean all
