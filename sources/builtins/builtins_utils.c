/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:15:27 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 15:48:34 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_node(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;
	t_env	*to_free;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			to_free = current;
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free_env_node(to_free);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	export_with_equal(t_minishell *shell, char *arg)
{
	char	*key;
	char	*value;
	char	*eq;

	eq = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, eq - arg);
	value = ft_strdup(eq + 1);
	if (is_valid_varname(key))
		add_env(&(shell->env_list), key, value);
	else
	{
		free(key);
		free(value);
		return (return_error("export", arg, "not a valid identifier"));
	}
	free(key);
	free(value);
	return (0);
}

int	export_without_equal(t_minishell *shell, char *arg)
{
	if (is_valid_varname(arg))
	{
		if (!update_existing_env(shell->env_list, arg, ""))
			add_env(&(shell->env_list), arg, "");
	}
	else
		return (return_error("export", arg, "not a valid identifier"));
	return (0);
}

void	ft_builtins_part1(t_minishell *shell, char **args, t_command *cmd, t_token **token, char **argv)
{
	int	exit_code;

	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(shell, args, cmd, token, argv);
	else if (ft_strcmp(args[0], "echo") == 0)
	{
		exit_code = ft_echo(args);
		if (shell)
			shell->exit_status = exit_code;
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		if (shell)
			shell->exit_status = ft_cd(args);
	}
	else
		ft_builtins_part2(shell, args);
}

void	ft_builtins_part2(t_minishell *shell, char **args)
{
	if (ft_strcmp(args[0], "env") == 0)
	{
		if (shell)
			shell->exit_status = ft_env(shell->env_list);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		if (shell)
			shell->exit_status = ft_export(shell, args);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		if (shell)
			shell->exit_status = ft_unset(&(shell->env_list), args);
	}
	else
	{
		if (shell)
		{
			fprintf(stderr, "minishell: %s: command not found\n", args[0]);
			shell->exit_status = 127;
		}
	}
}
