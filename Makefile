# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 14:56:07 by takira            #+#    #+#              #
#    Updated: 2022/10/25 14:56:09 by takira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

NAME		= libftprintf.a

SRCS		= ft_pirntf.c \
				ft_strlen.c \
              	ft_strchr.c \
              	ft_memset.c \
              	ft_bzero.c \
              	ft_memcpy.c \
              	ft_isdigit.c \
              	ft_calloc.c \
              	ft_itoa.c \
              	ft_putstr_fd.c \

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
