#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->value) // Only print variables with values
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		current = current->next;
	}
	return (0);
}

static int	remove_first_node(t_env **env_list, char *key)
{
	t_env	*temp;

	if (ft_strcmp((*env_list)->key, key) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free_env_node(temp);
		return (1);
	}
	return (0);
}

int	ft_unset(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list || !*env_list || !key)
		return (1);
	
	if (remove_first_node(env_list, key))
		return (0);
	
	prev = *env_list;
	current = prev->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			free_env_node(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
char *strip_quotes(const char *str)
{
    size_t len = ft_strlen(str);
    if ((str[0] == '"' && str[len - 1] == '"') ||
        (str[0] == '\'' && str[len - 1] == '\''))
    {
        char *res = malloc(len - 1);
        if (!res)
            return NULL;
		ft_strlcpy(res, str + 1, len - 1); // copy without first quote, leave space for null
        res[len - 2] = '\0';
        return res;
    }
    return ft_strdup(str);
}