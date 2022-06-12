NAME	= libft.a

SRCS		= ft_atoi.c	ft_isprint.c ft_putchar_fd.c	ft_striteri.c ft_strnstr.c \
		ft_bzero.c	ft_itoa.c	ft_putendl_fd.c	ft_strjoin.c	ft_strrchr.c \
		ft_calloc.c	ft_memchr.c	ft_putnbr_fd.c	ft_strlcat.c	ft_substr.c \
		ft_isalnum.c	ft_memcmp.c	ft_putstr_fd.c	ft_strlcpy.c	ft_tolower.c \
ft_isalpha.c	ft_memcpy.c	ft_split.c	ft_strlen.c	ft_toupper.c \
ft_isascii.c	ft_memmove.c	ft_strchr.c	ft_strmapi.c	ft_strtrim.c \
ft_isdigit.c	ft_memset.c	ft_strdup.c	ft_strncmp.c 

SRCS_BONUS	= ${SRCS} ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c

RM		= rm -f

HEAD	= libft.h

CFLAGS	= -Wall -Werror -Wextra

OBJS	=${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

all:	${NAME}

${NAME}:	${OBJS} ${HEAD}
			ar rc ${NAME} ${OBJS}
			ranlib	${NAME}

bonus:	${OBJS_BONUS} ${HEAD}
		ar rc ${NAME} ${OBJS_BONUS}
		ranlib ${NAME}


clean:	
		${RM} ${OBJS_BONUS}

fclean:	clean
		${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re bonus
