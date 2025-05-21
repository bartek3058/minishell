#include "../../includes/minishell.h"

void    parser_env(t_token **token, char **args)
{
    if (args[1])
        printf("env: too many arguments\n");
    add_token(token, "env", NULL);
}