# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 18:57:37 by yongckim          #+#    #+#              #
#    Updated: 2021/05/31 21:04:23 by yongckim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	srcs/cd.c \
				srcs/echo.c \
				srcs/env.c \
				srcs/execute_cmd.c \
				srcs/exit.c \
				srcs/export.c \
				srcs/pwd.c \
				srcs/unset.c \
				srcs/ft_error.c \
				srcs/bin_command.c \
				srcs/redirect_utils.c \
				srcs/redirect.c \
				srcs/pipe.c \
				srcs/export_env.c \
				srcs/main.c \
				srcs/check_syntax.c \
				srcs/handle_sig.c \
				srcs/list_util.c \
				srcs/parse_handle_env.c \
				srcs/parse_handle_quote.c \
				srcs/parse_handle_node.c \
				srcs/parse_manipulate_string.c \
				srcs/parse_util.c \
				srcs/parse.c \
				srcs/prompt.c \
				srcs/util.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-g3 -fsanitize=address #-Wall -Werror -Wextra

LIBDIR		=	libft/

LIB			=	libft.a

LIBCOM		=	-L./libft/ -lft

NAME		=	minishell

all			:	$(NAME)



$(NAME)		:	$(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) $(LIBCOM) -lncurses -o $(NAME) $(OBJS)

$(LIBFT)	:
				make -C $(LIBDIR)

clean		:
				make -C $(LIBDIR) clean
				rm -f $(OBJS)

fclean		:	clean
				rm -f libft.a
				rm -f $(NAME)

re			:	fclean all

norm		:
				norminette ./srcs/*.c *.h

.PHONY		:	all clean fclean re
