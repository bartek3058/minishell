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
int	is_valid_var_or_assign(const char *str)
{
	char	*eq;
	int		i;

	if(!str)
		return (0);
	eq = ft_strchr(str, '=');
	if (eq){
		if (eq == str)
			return (0);
		i = 0;
		while (&str[i] < eq)
		{
		if (i ==0 && !ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
		}
		return (1);
	}
	else
		return (is_valid_varname(str));
}
