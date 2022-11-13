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

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

NAME		= libftprintf.a

SRCS		= ft_isdigit.c ft_putchar_fd.c ft_putstr_fd.c ft_strchr.c ft_strlen.c\
			ft_printf.c compare_size.c input_printf_format.c print_num.c print_string.c vaild_info_for_each_fmt.c

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus:		all

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
