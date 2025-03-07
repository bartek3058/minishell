#include "../includes/minishell.h"

void	init_minishell(t_minishell *shell, char **envp)
{
	int i;
	char *key;
	char *value;
	char *eq_pos;
	// inicjalizacja podstawowych pol struktury
	shell->env_list = NULL;
	shell->commands = NULL;
	shell->exit_status = 0;
	shell->running = 1;
	shell->line = NULL;
	// inicjalizacja listy zmiennych srodowiskowych
	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=')
		if (eq_pos)
		{
			key = ft_substr(envp[i], 0, eq_pos - envp[i])
		}
}