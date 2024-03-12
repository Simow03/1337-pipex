# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 17:49:06 by mstaali           #+#    #+#              #
#    Updated: 2024/03/12 21:21:35 by mstaali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_B = pipex_b

CC = cc

CFLAGS = -Wall -Wextra -Werror 

M_SOURCES = main.c utils.c error_handle.c libft/ft_putstr_fd.c libft/ft_split.c \
	libft/ft_strjoin.c libft/ft_strlen.c libft/ft_substr.c libft/ft_strncmp.c \
	libft/ft_strdup.c

B_SOURCES = utils.c error_handle.c bonus/main_bonus.c bonus/utils_bonus.c \
	libft/ft_strjoin.c libft/ft_strlen.c libft/ft_substr.c libft/ft_strncmp.c \
	libft/ft_strdup.c libft/ft_split.c libft/ft_putstr_fd.c libft/ft_strchr.c\
	bonus/get_next_line_bonus.c

M_OBJECTS = $(M_SOURCES:.c=.o)

B_OBJECTS = $(B_SOURCES:.c=.o)

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o : bonus/%.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus : $(NAME_B)

$(NAME) : $(M_OBJECTS)
	$(CC) $(M_OBJECTS) -o $(NAME)

$(NAME_B) : $(B_OBJECTS)
	$(CC) $(B_OBJECTS) -o $(NAME_B)

clean :
	rm -f $(M_OBJECTS) $(B_OBJECTS)

fclean : clean
	rm -f $(NAME) $(NAME_B)

re : fclean all

.PHONY : all bonus clean fclean re