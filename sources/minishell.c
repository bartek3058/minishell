#include "../includes/minishell.h"

void	minishell_loop(t_minishell shell)
{
	while (1)
	{
		readline("minishell$ ");
		add_history();
		ft_builtins();
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell shell;

	init_minishell(&shell,envp);
	minishell_loop(shell);
}