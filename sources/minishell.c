#include "../includes/minishell.h"

void	parser_helper(char *args, t_token *token)
{
	if (ft_strncmp(args[i], "export", 6) == 0)
		parser_export(&token, args);
	else if (ft_strncmp(args[i], "unset", 5) == 0)
		parser_export(&token, args);
	else if (ft_strncmp(args[i], "env", 3) == 0)
		parser_export(&token, args);
	
}

void	parser(char **args, t_token *token)
{
	int	i;

	i = 0;
	while(args[i] != NULL)
	{
		if (ft_strncmp(args[i], "pwd", 3) == 0)
			parser_pwd(&token);
		else if (ft_strncmp(args[i], "echo", 4) == 0)
			parser_echo(&token, args);
		else if (ft_strncmp(args[i], "|", 1) == 0)
			parser_pipe(&token, args);
		else if (ft_strncmp(args[i], ">", 1) == 0)
			parser_redirect_output(&token, args);
		else if (ft_strncmp(args[i], "<", 1) == 0)
			parser_redirect_output(&token, args);
		else if (ft_strncmp(args[i], ">>", 1) == 0)
			parser_double_redirect_output(&token, args);
		else if (ft_strncmp(args[i], "<<", 1) == 0)
			parser_double_redirect_input(&token, args);
		else if (ft_strncmp(args[i], "cd", 1) == 0)
			parser_cd(&token, args);
		else
			parser_helper(args, &token);
	}

}

void	minishell_loop_helper(t_minishell *shell, char **args, t_token *token)
{
	if(shell->line[0] == '\0')
			free(shell->line);
		add_history(shell->line); // obsluga historii, poruszania sie strzalkami
		args = ft_split(shell->line, ' '); // dzielenie linii na argumenty
		parser(&args, &token);
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
	while (1)
	{
		shell->line = readline("minishell$ "); // wyswietlanie i czytanie prompta
		if(shell->line == NULL) // obsluga ctrl+d, ctrl+d zwraca NULL z readline
		{
			ft_putstr_fd("\n", 1);
			exit(shell->exit_status);
		}
		minishell_loop_helper(shell, args, &token);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell shell;
	t_token token;
	char **args;

	args = NULL;
	(void)argv;
	(void)(argc);
	init_minishell(&shell, envp, &token); // inicjalizacja zmiennych, w tym zmiennych srodowiskowych (envp)
	minishell_loop(&shell, args, &token); // glowna petla programu
}