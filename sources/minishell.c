#include "../includes/minishell.h"

void	minishell_loop(char *input)
{
	while (1)
	{
		input = readline("minishell$ ");
		if (input && *input)
			add_history(input);
		ft_builtins(input);
		free(input);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell shell;

	init_minishell(&shell,envp);

	minishell_loop();
}