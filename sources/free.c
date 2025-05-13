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

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}
