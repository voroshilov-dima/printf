# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 18:48:34 by dvoroshy          #+#    #+#              #
#    Updated: 2018/08/04 18:48:37 by dvoroshy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			 = libftprintf.a

CC 				 = gcc
CCFLAGS			 = -Wall -Werror -Wextra -pthread
SRC_FILES		 = main.c
				# rtv1.c			\

SRC_DIR			 = src/
OBJ_DIR			 = obj/
OBJ_FILES		 = $(SRC_FILES:.c=.o)
SRC				 = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				 = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT_FILE		 = libft.a
LIBFT_DIR		 = libft/
LIBFT_FLAGS		 = -lft -L $(LIBFT_DIR)
LIBFT			 = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
INC 			 = inc/

FLAGS			 = $(CCFLAGS) $(LIBFT_FLAGS)

FT_PRINTF_HEADER = ft_printf.h

all: $(NAME)

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
