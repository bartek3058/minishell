#include "../../includes/minishell.h"

static	int	ft_envsize(t_env *env)
{
	int size;
	t_env *current;

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
    char    **arr;
    int     count;
    t_env   *current;
    int     i;

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
    char **args;
    int i = 0;

    // Count tokens
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        return NULL;

    tmp = token;
    while (tmp)
    {
        args[i] = ft_strdup(tmp->value); // or strdup if you use libc
        i++;
        tmp = tmp->next;
    }
    args[i] = NULL;
    return args;
}