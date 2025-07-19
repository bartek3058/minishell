NAME	=	minishell

CC		=	cc

CFLAGS	=	-g -Wall -Wextra -Werror

READLINE = -lreadline

INCLUDE	=	./includes

SRCS	=	./sources/minishell.c\
					./sources/builtins/builtins.c\
					./sources/builtins/builtins_2.c\
					./sources/utils/utils.c\
					./sources/utils/utils_b.c\
					./sources/utils/utils_t.c\
					./sources/utils/utils_t_2.c\
					./sources/utils/utils_validations.c\
					./sources/utils/exec.c\
					./sources/redirections.c\
					./sources/pipes.c\
					./sources/free.c\
					./sources/init.c\
					./sources/parser/parser.c\
					./sources/parser/parser1.c\
					./sources/parser/token_proc.c\
					./sources/parser/expansion.c\
					./sources/parser/smart_split.c

				
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
