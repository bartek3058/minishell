#include "../../includes/minishell.h"

void	ft_echo(char *input)
{
	int i;

	i = 0;
	
	if (input[5] == '-' && input[6] == 'n' && input[7] == ' ')
	{
		i = 8;
		while (input[i] != '\0')
		{
			write(1, &input[i], 1);
			i++;
		}
	}
	else
	{
		i = 5;
		while (input[i] != '\0')
		{
			write(1, &input[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
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

void	ft_builtins(char *input)
{
	if (input && (ft_strncmp(input, "pwd", 3) == 0))
		ft_pwd();
	else if (input && (ft_strncmp(input, "exit", 4) == 0))
		ft_exit();
	else if (input && (ft_strncmp(input, "echo ", 5) == 0))
		ft_echo(input);
}