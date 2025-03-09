#include "../includes/minishell.h"

void	free_args(char **args)
{
	int i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		i++;
	while(i >= 0)
	{
		free(args[i]);
		args[i] = NULL;
		i--;
	}
	free(args);
	args = NULL;
}