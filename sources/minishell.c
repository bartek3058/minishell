#include "../includes/minishell.h"

void	minishell_loop_helper(t_minishell *shell, char **args, t_token **token)
{
	if(shell->line[0] == '\0')
			free(shell->line);
		add_history(shell->line); // obsluga historii, poruszania sie strzalkami
		args = ft_split(shell->line, ' '); // dzielenie linii na argumenty
		parser(args, token);
		if (!args)
		{
			free(shell->line);
			return ;
		}
		ft_builtins(shell, args); // obsluga builtins (pwd, echo, ...)
		free_args(args);
		free(shell->line);
}

void	minishell_loop(t_minishell *shell, char **args, t_token *token)
{
	while(1) // glowna petla
	{
		shell->line = readline("minishell$ "); // wyswietlanie i czytanie prompta
		if(shell->line == NULL) // obsluga ctrl+d, ctrl+d zwraca NULL z readline
		{
			ft_putstr_fd("\n", 1);
			exit(shell->exit_status);
		}
		minishell_loop_helper(shell, args, &token);
	}
	free_env(shell->env_list);
	shell->env_list = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_minishell shell;
	t_token token;
	char **args;
	int test_nr;

	args = NULL;
	(void)argv;
	(void)(argc);

	init_minishell(&shell,envp, &token); // inicjalizacja zmiennych, w tym zmiennych srodowiskowych (envp)
	
	//testy
	test_nr = atoi(argv[2]);
	
	if (argc > 1 && ft_strcmp(argv[1], "--test") == 0)
		ft_test_command_handler(&shell, &test_nr); // uruchomienie testow
	else
		minishell_loop(&shell, args, &token); // glowna petla programu

	free_env(shell.env_list); // zwolnienie pamieci po zmiennych srodowiskowych
	return (0);
}