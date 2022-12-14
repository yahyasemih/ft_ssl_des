# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 17:48:29 by yez-zain          #+#    #+#              #
#    Updated: 2022/12/14 15:43:09 by yez-zain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
LDFLAGS = -lreadline
SRCS = ft_ssl.c main.c md5/md5.c base64/base64.c base64/encode.c base64/decode.c\
	utils/commands_utils.c utils/ft_read_block.c utils/libc_utils.c\
	sha256/sha256.c md5/state_operations.c md5/string_operations.c\
	utils/swap_bytes.c utils/write_in_hex.c sha256/state_operations.c\
	sha256/string_operations.c sha256/block_operations.c utils/parse_commands.c\
	md5/block_operations.c utils/free_args.c des/des_cbc.c des/des_ecb.c\
	des/helpers.c utils/ft_strjoin.c utils/hex_str_to_int.c utils/get_password.c\
	utils/int_to_hex_str.c des/des_routines.c des/pbkdf.c
DEPS = $(SRCS:.c=.d)
OBJECTS = $(SRCS:.c=.o)
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

all: $(NAME)

$(NAME): $(OBJECTS) Makefile
	@echo "$(RED)Compiling $(NAME)...$(NC)"
	@echo "$(RED)Linking...$(NC)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)Finished linking && compiling...$(NC)"

%.c:

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(RED)Compiling $< ...$(NC)"

%.d: %.c
	@$(CC) $(CFLAGS) -MM -o $@ $<

clean:
	@echo "$(RED)Cleaning objects...$(NC)"
	@rm -rf $(OBJECTS) $(DEPS)
	@echo "$(GREEN)Cleaned objects...$(NC)"

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@echo "$(GREEN)Cleaned $(NAME)...$(NC)"

re: fclean all

-include $(DEPS)
