#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	char	*stripped;
	int		i;
	int		n_flag;
	
	i = 1;
	n_flag = 0;	
	if (args[i] && ft_strcmp(args[i], "-n") == 0){
		n_flag = 1;
		i++;
	}
	while (args[i]){
		stripped = strip_quotes(args[i]);
		ft_putstr_fd(stripped, 1);
		free(stripped);
		if (args[i + 1]) // jesli jest nastepny argument dodaj spacje
			write(1, " ", 1);
		i++;
	}
	if(!n_flag) // jesli nie ma flagi -n dodaj nowa linie
		write(1, "\n", 1);
	return (0); // zwroc 0 jako kod wyjscia (sukces)
}

static int	parse_exit_code(const char *str)
{
	int		result;
	char	*stripped;

	stripped = strip_quotes(str);
	if (!stripped)
		return(0);
	result = ft_atoi(stripped);
	free(stripped);
	return(result & 255);
}

void	ft_exit(t_minishell *shell, char **args)
{
	int		arg_count;
	int		exit_code;

	arg_count = count_args(args);
	if (arg_count > 1){
		shell->exit_status = return_error("cd", "", "too many arguments");
		return;
	}
	if (arg_count == 0)
		exit_code = shell->exit_status;
	else{
		if(!validate_numeric_arg(args[1])){
			return_error("exit", args[1], "numeric argument required");
			free_env(shell->env_list); // zwalniamy pamiec dla zmiennych srodowiskowych
			shell->env_list = NULL; // ustawiamy wskaznik na NULL, zapobiega double free
			exit(2); // zwraca status wyjscia			
		}
		exit_code = parse_exit_code(args[1]);
	}
	free_env(shell->env_list); // zwalniamy pamiec dla zmiennych srodowiskowych
	shell->env_list = NULL; // ustawiamy wskaznik na NULL, zapobiega double free
	exit(exit_code); // zwraca status wyjscia
}

void	ft_pwd()
{
	char cwd[1024];

	if(getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

int	ft_cd(char **args) 
{
	const char	*path;
	int			arg_count;
	
	arg_count = count_args(args);
	if (arg_count > 1)
		return(return_error("cd", "", "too many arguments"));
	else if (!args[1]) 
	{
		path = getenv("HOME");
		if (!path) 
		{
			return (return_error("cd", args[1], "path not set"));
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0) 
	{
		perror("cd() error");
		return 1;
	}
	return 0;
}

void	ft_builtins(t_minishell *shell, char **args)
{
	int	exit_code;
	
	if (!args || !args[0])
		return;
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "exit") == 0){
		ft_exit(shell, args);
//		shell->running = 0; // ustawienie flagi do zakonczenia petli
	}
	else if (ft_strcmp(args[0], "echo") == 0)
	{
		exit_code = ft_echo(args);
		if(shell)
			shell->exit_status = exit_code;
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		if (shell)
			shell->exit_status = ft_cd(args); 
	}
	else if (ft_strcmp(args[0], "env") == 0)
	{
		if (shell)
			shell->exit_status = ft_env(shell->env_list);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		if(shell)
			shell->exit_status = ft_export(shell, args);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		if(shell)
			shell->exit_status = ft_unset(&(shell->env_list), args); // pass args
	}
	else
	{
		if (shell)
		{
			fprintf(stderr, "minishell: %s: command not found\n", args[0]);
			shell->exit_status = 127; // command not found
		}
	}
}
