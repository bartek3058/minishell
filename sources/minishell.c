#include "../includes/minishell.h"

void	minishell_loop_helper(t_minishell *shell, char **args, t_token **token)
{
	char	**exec_args;
	t_token	*current;
	t_token *cmd_start;
	t_token *cmd_end;

	if(shell->line[0] == '\0') {
		free(shell->line);
		return ; // jesli linia jest pusta, nic nie robimy
	}
	add_history(shell->line); // obsluga historii, poruszania sie strzalkami
	args = ft_split(shell->line, ' '); // dzielenie linii na argumenty
	parser(args, token);
	current = *token; // ustawienie aktualnego tokena na poczatek listy
	while (current){
		cmd_start = current; // zapisanie poczatku polecenia
		cmd_end = current; // zapisanie konca polecenia
		while (cmd_end && (!cmd_end->type || ft_strcmp(cmd_end->type, "PIPE") != 0))
			cmd_end = cmd_end->next;
		exec_args = tokens_to_args(cmd_start); // konwersja listy tokenow na tablice argumentow
		// 3. Handle redirections for this command (search for redirection tokens in this segment)
		//e.g. if you find a token with type "REDIRECT_OUTPUT", set up output redirection
		if (!exec_args || !exec_args[0]) { // sprawdzenie czy polecenie jest puste
			free(shell->line);
			free_args(args);
			if (exec_args)
				free_args(exec_args); // zwolnienie pamieci po tablicy argumentow
			return ;
		}
		if (is_builtin(exec_args[0])) // sprawdzenie czy polecenie jest wbudowane
			ft_builtins(shell, exec_args); // obsluga builtins (pwd, echo, ...)
		else
			execute_cmd(check_path(exec_args[0]), exec_args); // wykonanie polecenia
		free_args(exec_args); // zwolnienie pamieci po tablicy argumentow
		if (current == cmd_end)
			current = cmd_end->next; // przejscie do nastepnego polecenia
		else
			current = NULL; // jesli nie ma nastepnego polecenia, konczymy petle
	}
	free_args(args);
	free(shell->line);
	free_tokens(*token);
	*token = NULL;
}

void	minishell_loop(t_minishell *shell, char **args, t_token **token)
{
	while(1) // glowna petla
	{
		shell->line = readline("minishell$ "); // wyswietlanie i czytanie prompta
		if(shell->line == NULL) // obsluga ctrl+d, ctrl+d zwraca NULL z readline
		{
			ft_putstr_fd("\n", 1);
			exit(shell->exit_status);
		}
		minishell_loop_helper(shell, args, token);
	}
	free_env(shell->env_list);
	shell->env_list = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_minishell shell;
	t_token *token;
	char **args;
	int test_nr;

	args = NULL;
	token = NULL;
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