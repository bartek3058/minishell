#include "../../includes/minishell.h"

int	ft_cd(char **args) 
{
	const char	*path;
	int			arg_count;
	
	arg_count = count_args(args);
	if (arg_count > 1)
		return(return_error("cd", "", "too many arguments"));
	else if (!args[1]) 
	{
		path = getenv("HOME");
		if (!path) 
		{
			return (return_error("cd", args[1], "path not set"));
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0) 
	{
		perror("cd() error");
		return 1;
	}
	return 0;
}