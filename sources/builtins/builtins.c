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

int	parse_exit_code(const char *str)
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

void	ft_exit(t_fork_ctx *ctx, t_command *cmd, char **argv)
{
	int	arg_count;
	int	exit_code;

	arg_count = count_args(ctx->args);
	if (arg_count > 1)
	{
		ctx->shell->exit_status = return_error("cd", "", "too many arguments");
		return ;
	}
	if (arg_count == 0)
		exit_code = ctx->shell->exit_status;
	else
		exit_code = get_exit_code(ctx);
	cleanup_and_exit(ctx, cmd, argv, exit_code);
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	ft_builtins(t_fork_ctx *ctx, t_command *cmd, char **argv)
{
	if (!ctx->args || !ctx->args[0])
		return ;
	ft_builtins_part1(ctx, cmd, argv);
}
