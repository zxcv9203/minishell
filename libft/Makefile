# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/06 16:44:20 by yongckim          #+#    #+#              #
#    Updated: 2021/05/30 21:10:25 by yongckim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_strcmp.c \
			ft_strlen.c \
			ft_atoll.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_memmove.c \
			ft_strjoin2.c \
			ft_llrange.c \
			ft_isnum.c \
			ft_putstr_fd.c \
			ft_getenv.c \
			ft_strdup.c \
			ft_memcpy.c \
			ft_split.c \
			ft_strchr.c \
			ft_arrsize.c \
			ft_doublefree.c \
			ft_isenv.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	#-Wall -Werror -Wextra -g3 -fsanitize=address

LIBMAKE	=	ar rcsv

REMOVE	=	rm -f

NAME	=	libft.a

all		:	$(NAME)

$(NAME) :	$(OBJS)
			$(LIBMAKE) $(NAME) $(OBJS)

clean	:
			$(REMOVE) $(OBJS)

fclean	:	clean
			$(REMOVE) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
