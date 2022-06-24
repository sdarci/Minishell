# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 16:09:07 by sdarci            #+#    #+#              #
#    Updated: 2022/06/24 17:37:11 by sdarci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBDIR = /Users/sdarci/Downloads/minishellmake/parsing/LIBFT

SRCS =	main.c pipe.c cd.c echo.c utils.c buildins.c exit.c execute_simple.c parsing/quots.c\
			redirect_out.c parsing/parsing.c parsing/cmd.c parsing/redirs.c parsing/shell_split.c parsing/ft_exp.c\
			parsing/change_env.c parsing/lists_func.c \
			utils2.c utils3.c unset.c execute_simple1.c signalss.c\
			exportt.c\
			parsing/LIBFT/ft_split.c \
			parsing/LIBFT/ft_strdup.c parsing/LIBFT/ft_strjoin.c parsing/LIBFT/ft_strncmp.c \
			parsing/LIBFT/ft_strtrim.c  parsing/LIBFT/ft_memcpy.c \
			parsing/LIBFT/ft_strchr.c parsing/LIBFT/ft_strcmp.c parsing/LIBFT/ft_putstr_fd.c \
			parsing/LIBFT/ft_putchar_fd.c 
			
			
			
HEADER = minishell.h

FT_DIR = parsing/LIBFT

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -fsanitize=address -g

RM = rm -f

all: $(NAME)


$(NAME): $(OBJS)
	 $(CC) $(CFLAGS) $(OBJS) -lreadline -L ${FT_DIR} -o $(NAME)

$(OBJS): $(HEADER) Makefile

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o  $@ 
	
clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
