#include "../../includes/minishell.h"

static	int	ft_envsize(t_env *env)
{
	int		size;
	t_env	*current;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
char	**conv_env_to_array(t_env *env)
{
	char	**arr;
	int		count;

	count = ft_envsize(env);
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill_env_array(env, arr))
		return (NULL);
	return (arr);
}

char	**tokens_to_args(t_token *token)
{
	char	**args;
	int		count;

	count = count_tokens_2(token);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	fill_args_array(args, token);
	return (args);
}
char *get_env_value(t_env *env_list, char *key)
{
	t_env	*current;

	current = env_list;
	while(current){
		if(ft_strcmp(current->key, key) == 0)
			return current->value;
		current = current->next;
	}
	return NULL;
}