#include "../includes/minishell.h"

void minishell_loop_helper(t_minishell *shell, char **args, t_token **token)
{
	t_command *cmd_list;

	if (shell->line[0] == '\0')
	{
		free(shell->line);
		return;
	}
	add_history(shell->line);
	args = smart_split(shell->line);
	// Phase 1: Tokenize (modified existing parser)
	tokenize_input(args, token);
	// Phase 2: Group into commands (new function)
	cmd_list = parse_command_chain(*token, shell);
	if (!cmd_list)
	{
		cleanup_and_return(args, shell->line, *token);
		return;
	}
	// Execute command chain
	shell->exit_status = execute_command_chain(shell, cmd_list);
	// Cleanup
	free_command_list(cmd_list);
	cleanup_and_return(args, shell->line, *token);
	*token = NULL;
}

void	minishell_loop(t_minishell *shell, char **args, t_token **token)
{
	while(shell->running) // glowna petla
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

	args = NULL;
	token = NULL;
	(void)argv;
	(void)(argc);

	init_minishell(&shell,envp, &token); // inicjalizacja zmiennych, w tym zmiennych srodowiskowych (envp)
	minishell_loop(&shell, args, &token); // glowna petla programu
	free_env(shell.env_list); // zwolnienie pamieci po zmiennych srodowiskowych
	return (0);
}



void free_command_list(t_command *cmd_list)
{
    t_command *current = cmd_list;
    t_command *next;
    
    while (current)
    {
        next = current->next;
        if (current->args)
            free_args(current->args);
        if (current->input_files)
            free(current->input_files);
        if (current->output_files)
            free(current->output_files);
        if (current->append_files)
            free(current->append_files);
        if (current->heredoc)
            free(current->heredoc);
        free(current);
        current = next;
    }
}