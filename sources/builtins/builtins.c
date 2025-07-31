/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomek <tomek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:06:40 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/31 23:08:26 by tomek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int		i;
	int		n_flag;

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
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}

static int	parse_exit_code(const char *str)
{
	int		result;
	char	*stripped;

	stripped = strip_quotes(str);
	if (!stripped)
		return (0);
	result = ft_atoi(stripped);
	free(stripped);
	return (result & 255);
}

void	ft_exit(t_minishell *shell, char **args, t_command *cmd, t_token **token, char **argv)
{
	int		arg_count;
	int		exit_code;

	arg_count = count_args(args);
	if (arg_count > 1)
	{
		shell->exit_status = return_error("cd", "", "too many arguments");
		return ;
	}
	if (arg_count == 0)
		exit_code = shell->exit_status;
	else
	{
		if (!validate_numeric_arg(args[1]))
		{
			return_error("exit", args[1], "numeric argument required");
			free_env(shell->env_list);
			shell->env_list = NULL;
			exit(2);
		}
		exit_code = parse_exit_code(args[1]);
	}
	free_env(shell->env_list);
	shell->env_list = NULL;
	free_command_list(cmd);
	free_args(argv);
	free_tokens(*token);
	exit(exit_code);
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	ft_builtins(t_minishell *shell, char **args, t_command *cmd, t_token **token, char **argv)
{
	if (!args || !args[0])
		return ;
	ft_builtins_part1(shell, args, cmd, token, argv);
}
