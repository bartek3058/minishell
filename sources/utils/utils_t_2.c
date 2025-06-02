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
		arr[i] = ft_strjoin(current->key, "=");
		arr[i] = ft_strjoin(arr[i], current->value);
		if (!arr[i])
		{
			free_args(arr);
			return (0); 
		}
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char **tokens_to_args(t_token *token)
{
    int count = 0;
    t_token *tmp = token;

    // Count: command + all value tokens (including value of first token)
    while (tmp)
    {
        count++; // one for each token
        tmp = tmp->next;
    }

    char **args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        return NULL;

    tmp = token;
    int i = 0;
    // Always put command name
    args[i++] = ft_strdup(token->type);

    // If first token has a value, add it
    if (token->value)
        args[i++] = ft_strdup(token->value);

    // Add values of all subsequent tokens
    tmp = token->next;
    while (tmp)
    {
        if (tmp->value)
            args[i++] = ft_strdup(tmp->value);
        tmp = tmp->next;
    }
    args[i] = NULL;
    return args;
}
