# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcerrito <dcerrito@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 08:06:16 by dcerrito          #+#    #+#              #
#    Updated: 2022/05/03 20:41:58 by dcerrito         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
FRM = rm -rf
CFLAGS = -Iincludes -Wall -Wextra -Werror
MAIN = main.c
LIBFT = \
	libft/ft_split.c			\
	libft/ft_strcpy.c			\
	libft/ft_strjoin.c		\
	libft/ft_strlcat.c		\
	libft/ft_strlcpy.c		\
	libft/ft_strlen.c			\
	libft/ft_strnstr.c		\
	libft/ft_substr.c	\

UTILS = \
	utils/executes.c	\
	utils/free_all.c	\

SRCS = $(LIBFT) $(UTILS) $(MAIN)
OBJS = $(patsubst %.c, %.o, $(SRCS))
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
all: $(NAME)
clean:
	$(FRM) $(OBJS)
fclean: clean
	$(FRM) $(NAME)
re: fclean all
.PHONY: re clean fclean all