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

void	ft_exit()
{
	exit(0);
}

void	ft_pwd()
{
	char cwd[1024];

	if(getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	ft_builtins(t_minishell shell, char **args)
{
	if (shell.line && (ft_strcmp(shell.line, "pwd") == 0))
		ft_pwd();
	else if (shell.line && (ft_strcmp(shell.line, "exit") == 0))
		ft_exit();
	else if (shell.line && (ft_strcmp(shell.line, "echo") == 0))
		shell.exit_status = ft_echo(args);
}