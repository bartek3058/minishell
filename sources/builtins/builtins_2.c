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

	if (!env_list || !*env_list)
		return 0;
	if (ft_strcmp((*env_list)->key, key) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free_env_node(temp);
		return (1);
	}
	return (0);
}

int ft_unset(t_env **env_list, char **args)
{
    t_env *current;
    t_env *prev;
    t_env *to_free;
    int i;
    int ret;

    i = 1;
    ret = 0;
    while (args[i])
    {
        ret = remove_first_node(env_list, args[i]);
        if (!ret)
        {
            current = *env_list;
            prev = NULL;
            while (current)
            {
                if (ft_strcmp(current->key, args[i]) == 0)
                {
                    to_free = current;
                    if (prev)
                        prev->next = current->next;
                    else
                        *env_list = current->next;
                    free_env_node(to_free);
                    break;
                }
                prev = current;
                current = current->next;
            }
        }
        i++;
    }
    return (0);
}

char *strip_quotes(const char *str)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	quote;
	
	if (!str)
		return NULL;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return NULL;
	i = 0;
	j = 0;
	quote = 0;
	while (str[i]){
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else if (quote && str[i] == quote){
			quote = 0;
			i++;
			}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return res;
}

int ft_export(t_minishell *shell, char **args)
{
	int i;
	char *eq;
	char *key;
	char *value;

	if (!args[1])
		return (ft_env(shell->env_list));
	i = 1;
	while (args[i]){
		eq = ft_strchr(args[i], '=');
		if (eq){
			key = ft_substr(args[i], 0, eq - args[i]);
			value = ft_strdup(eq + 1);
			if (is_valid_varname(key))
				add_env(&(shell->env_list), key, value);
			else
				return (return_error("export", args[i], "not a valid identifier"));
			free(key);
			free(value);
		}
		else{
			if (is_valid_varname(args[i])){
				if (!update_existing_env(shell->env_list, args[i], ""))
					add_env(&(shell->env_list), args[i], "");
			}
			else
				return (return_error("export", args[i], "not a valid identifier"));
		}
		i++;
	}
	return (0);
}
