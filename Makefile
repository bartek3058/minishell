NAME	=	minishell

CC		=	cc

CFLAGS	=	-g -Wall -Wextra -Werror

READLINE = -lreadline

INCLUDE	=	./includes

SRCS	=	./sources/minishell.c\
					./sources/builtins/builtins.c\
					./sources/utils/utils.c\
					./sources/init.c\
					./sources/free.c
				
OBJS	=	${SRCS:.c=.o}

LIBPATH	=	libft/

LIBFT = $(LIBPATH)libft.a

${LIBFT}:
			make -C ${LIBPATH}

all:		${NAME}

${NAME}:	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(READLINE) -o $(NAME) $(OBJS) $(LIBFT)

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
