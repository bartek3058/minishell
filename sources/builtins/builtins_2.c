/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:22:55 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 11:13:15 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->value)
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
		return (0);
	if (ft_strcmp((*env_list)->key, key) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free_env_node(temp);
		return (1);
	}
	return (0);
}

int	ft_unset(t_env **env_list, char **args)
{
	int	i;
	int	ret;

	i = 1;
	while (args[i])
	{
		ret = remove_first_node(env_list, args[i]);
		if (!ret)
			remove_env_node(env_list, args[i]);
		i++;
	}
	return (0);
}

char	*strip_quotes(const char *str)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	quote;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else if (quote && str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

int	ft_export(t_minishell *shell, char **args)
{
	int	i;

	if (!args[1])
		return (ft_env(shell->env_list));
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (export_with_equal(shell, args[i]))
				return (1);
		}
		else
		{
			if (export_without_equal(shell, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
