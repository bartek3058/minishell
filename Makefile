NAME	=	minishell

CC		=	cc

CFLAGS	=	-g -Wall -Wextra -Werror

INCLUDE	=	./includes

SRCS	=	./sources/minishell.c
				
OBJS	=	${SRCS:.c=.o}

LIBPATH	=	libft/

LIBFT = $(LIBPATH)libft.a

${LIBFT}:
			make -C ${LIBPATH}

all:		${NAME}

${NAME}:	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o:	%.c
		$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
			make clean -C ${LIBPATH}
			rm -f ${OBJS}
fclean:		clean
			make fclean -C ${LIBPATH}
			rm -f ${NAME}

re:				fclean all

.PHONY:		all clean fclean re
