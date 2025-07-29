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
int	handle_env_entry(t_env *current, char **arr, int i)
{
	char	*tmp;

	tmp = ft_strjoin(current->key, "=");
	if (!tmp)
		return (0);
	if (current->value)
		arr[i] = ft_strjoin(tmp, current->value);
	else
		arr[i] = ft_strdup(tmp);
	free(tmp);
	if (!arr[i])
		return (0);
	return (1);
}

int	fill_env_array(t_env *env, char **arr)
{
	t_env	*current;
	int		i;

	current = env;
	i = 0;
	while (current)
	{
		if (!handle_env_entry(current, arr, i))
		{
			free_args(arr);
			return (0);
		}
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (1);
}
int	count_tokens_2(t_token *token)
{
	int count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	fill_args_array(char **args, t_token *token)
{
	int i = 0;

	args[i++] = ft_strdup(token->type);
	if (token->value)
		args[i++] = ft_strdup(token->value);
	token = token->next;
	while (token)
	{
		if (token->value)
			args[i++] = ft_strdup(token->value);
		token = token->next;
	}
	args[i] = NULL;
}