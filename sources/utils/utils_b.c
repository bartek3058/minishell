#include "../../includes/minishell.h"

int is_redirect_or_pipe(char *arg)
{
    return (!ft_strcmp(arg, ">") || !ft_strcmp(arg, "<") ||
            !ft_strcmp(arg, ">>") || !ft_strcmp(arg, "<<") ||
            !ft_strcmp(arg, "|") || !ft_strcmp(arg, "&&") ||
            !ft_strcmp(arg, "||"));
}