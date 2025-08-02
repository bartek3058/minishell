/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:04:46 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/29 17:06:25 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **args)
{
	const char	*path;
	int			arg_count;

	arg_count = count_args(args);
	if (arg_count > 1)
		return (return_error("cd", "", "too many arguments"));
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
		return (1);
	}
	return (0);
}

int	get_exit_code(t_fork_ctx *ctx)
{
	if (!validate_numeric_arg(ctx->args[1]))
	{
		return_error("exit", ctx->args[1], "numeric argument required");
		free_env(ctx->shell->env_list);
		ctx->shell->env_list = NULL;
		exit(2);
	}
	return (parse_exit_code(ctx->args[1]));
}

void	cleanup_and_exit(t_fork_ctx *ctx, t_command *cmd, char **argv, int code)
{
	free_env(ctx->shell->env_list);
	ctx->shell->env_list = NULL;
	free_command_list(cmd);
	free_args(argv);
	free_tokens(*(ctx->token));
	exit(code);
}

void	process_strip_quotes(t_strip_ctx *ctx)
{
	while (ctx->str[ctx->i])
	{
		if (!ctx->quote && (ctx->str[ctx->i] == '\''
				|| ctx->str[ctx->i] == '"'))
			ctx->quote = ctx->str[(ctx->i)++];
		else if (ctx->quote && ctx->str[ctx->i] == ctx->quote)
		{
			ctx->quote = 0;
			(ctx->i)++;
		}
		else
			ctx->res[(ctx->j)++] = ctx->str[(ctx->i)++];
	}
}
