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
	char	*tmp;
	int		count;
	t_env	*current;
	int		i;

	count = ft_envsize(env);
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		if (!tmp)
		{
			free_args(arr);
			return (NULL); // zwolnienie pamieci w przypadku bledow
		}
		if (current->value)
			arr[i] = ft_strjoin(tmp, current->value);
		else
			arr[i] = ft_strdup(tmp);
		free(tmp);
		if (!arr[i])
		{
			free_args(arr);
			return (NULL); 
		}
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char **tokens_to_args(t_token *token)
{
	int 	count;
	int 	i;
	char	**args;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp){
		count++; // one for each token
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return NULL;
	tmp = token;
	i = 0;
	args[i++] = ft_strdup(token->type);
	if (token->value)
		args[i++] = ft_strdup(token->value);
	tmp = token->next;
	while (tmp){
		if (tmp->value)
			args[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	args[i] = NULL;
	return args;
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