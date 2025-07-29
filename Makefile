NAME	=	minishell

CC		=	cc

CFLAGS	=	-g -Wall -Wextra -Werror

READLINE = -lreadline

INCLUDE	=	./includes

SRCS	=	./sources/minishell.c\
					./sources/builtins/builtins.c\
					./sources/builtins/builtins_2.c\
					./sources/builtins/builtins_utils.c\
					./sources/builtins/builtins_utils_2.c\
					./sources/utils/utils.c\
					./sources/utils/utils_b.c\
					./sources/utils/utils_b_2.c\
					./sources/utils/utils_b_3.c\
					./sources/utils/utils_t.c\
					./sources/utils/utils_t_2.c\
					./sources/utils/utils_validations.c\
					./sources/utils/exec.c\
					./sources/redirections/redirections.c\
					./sources/redirections/redirections_utils.c\
					./sources/redirections/redirections_utils_2.c\
					./sources/pipes/pipes.c\
					./sources/pipes/pipes_utils.c\
					./sources/pipes/pipes_utils_2.c\
					./sources/free/free.c\
					./sources/free/free_2.c\
					./sources/init.c\
					./sources/parser/parser.c\
					./sources/parser/parser1.c\
					./sources/parser/parser2.c\
					./sources/parser/parser_3.c\
					./sources/parser/parser_4.c\
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
