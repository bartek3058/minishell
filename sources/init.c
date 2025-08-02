/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:34:20 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/29 17:38:47 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_existing_env(t_env *env_list, char *key, char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	add_env(t_env **env_list, char *key, char *value)
{
	t_env	*new_env;
	t_env	*current;

	if (*env_list && update_existing_env(*env_list, key, value))
		return (0);
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = new_env;
		return (0);
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_env;
	return (0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_minishell(t_minishell *shell, char **envp, t_token **token)
{
	shell->env_list = NULL;
	shell->commands = NULL;
	shell->exit_status = 0;
	shell->running = 1;
	shell->line = NULL;
	*token = NULL;
	init_env_list(shell, envp);
	setup_signals();
}
