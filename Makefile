NAME	=	minishell

CC		=	cc

CFLAGS	=	-g -Wall -Wextra -Werror

READLINE = -lreadline

INCLUDE	=	./includes

SRCS	=	./sources/minishell.c\
					./sources/builtins/builtins.c\
					./sources/builtins/builtins_2.c\
					./sources/utils/utils.c\
					./sources/utils/utils_t.c\
					./sources/init.c\
					./sources/free.c
				
OBJS	=	${SRCS:.c=.o}

LIBPATH	=	libft/

LIBFT = $(LIBPATH)libft.a

all:		${LIBFT} ${NAME}

${LIBFT}:
			make -C ${LIBPATH}

${NAME}:	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE) 

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
