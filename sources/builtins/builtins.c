#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int i;
	int n_flag;
	
	i = 1;
	n_flag = 0;
	
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1]) // jesli jest nastepny argument dodaj spacje
			write(1, " ", 1);
		i++;
	}
	if(!n_flag) // jesli nie ma flagi -n dodaj nowa linie
		write(1, "\n", 1);
	return (0); // zwroc 0 jako kod wyjscia (sukces)
}

void	ft_exit(t_minishell *shell)
{
	free_env(shell->env_list); // zwalniamy pamiec dla zmiennych srodowiskowych
	shell->env_list = NULL; // ustawiamy wskaznik na NULL, zapobiega double free
	exit(shell->exit_status); // zwraca status wyjscia
}

void	ft_pwd()
{
	char cwd[1024];

	if(getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

int	ft_cd(char **args) {
	if (!args[1]) {
		fprintf(stderr, "minishell: cd: missing argument\n");
		return 1;
	}
	if (chdir(args[1]) != 0) {
		perror("cd() error");
		return 1;
	}
	else {
		chdir(args[1]);
		return 0;
	}
}


void	ft_builtins(t_minishell *shell, char **args)
{
	if (!args || !args[0])
		return;
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		ft_exit(shell);
		shell->running = 0; // ustawienie flagi do zakonczenia petli
	}
	else if (ft_strcmp(args[0], "echo") == 0)
		shell->exit_status = ft_echo(args); // pass args after "echo"
	else if (ft_strcmp(args[0], "cd") == 0)
		shell->exit_status = ft_cd(args); // pass args after "cd"
}