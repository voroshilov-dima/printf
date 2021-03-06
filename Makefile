# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 18:48:34 by dvoroshy          #+#    #+#              #
#    Updated: 2018/09/15 11:23:50 by dvoroshy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			 = libftprintf.a

CC 				 = gcc
CCFLAGS			 = -Wall -Werror -Wextra -pthread
SRC_FILES		 =	main.c						\
					support_functions1.c		\
					support_functions2.c		\
					support_functions3.c		\
					parse_format.c				\
					print_non_numbers.c			\
					print_signed_numbers.c		\
					print_unicode.c				\
					print_unsigned_numbers.c

SRC_DIR			 = srcs/
OBJ_DIR			 = obj/
OBJ_FILES		 = $(SRC_FILES:.c=.o)
SRC				 = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				 = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT_FILE		 = libft.a
LIBFT_DIR		 = libft/
LIBFT_FLAGS		 = -lft -L $(LIBFT_DIR)
LIBFT			 = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
INC 			 = includes/

FLAGS			 = $(CCFLAGS) $(LIBFT_FLAGS)

FT_PRINTF_HEADER = ft_printf.h

all: $(NAME)

ft_printf: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	ar -cvq $(NAME) $(OBJ) $(LIBFT_DIR)*.o

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)$(FT_PRINTF_HEADER)
	$(CC) $(CCFLAGS) -I $(INC) -I $(LIBFT_DIR) -c $< -o $@ 

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
