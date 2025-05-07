#include "../includes/minishell.h"

void	free_args(char **args)
{
	int i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	i++;
	while (i>= 0)
	{
		free(args[i]);
		args[i] = NULL;	
		i--;
	}
	free(args);
}
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
	env = NULL;
}