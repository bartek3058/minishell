#include "../../includes/minishell.h"

int is_redirect_or_pipe(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strcmp(arg, "|") || !ft_strcmp(arg, "&&") ||
		!ft_strcmp(arg, "||"))
		return (1);
	if (ft_strncmp(arg, ">>", 2) == 0 || ft_strncmp(arg, "<<", 2) == 0)
		return (1);
	if (arg[0] == '>' || arg[0] == '<')
		return (1);
	return (0);
}