/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:10:17 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 15:40:20 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin_command(t_minishell *shell, t_command *cmd,
		t_token **token, char **argv)
{
	int			stdin_copy;
	int			stdout_copy;
	t_fork_ctx	ctx;

	ctx.shell = shell;
	ctx.args = cmd->args;
	ctx.token = token;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (setup_redirections(cmd) < 0)
	{
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdin_copy);
		close(stdout_copy);
		shell->exit_status = 1;
		return (1);
	}
	ft_builtins(&ctx, cmd, argv);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (shell->exit_status);
}

int	count_pipe_commands_2(t_command *start_cmd)
{
	int			count;
	t_command	*current;

	count = 0;
	current = start_cmd;
	while (current && current->pipe_out)
	{
		count++;
		current = current->next;
	}
	return (count + 1);
}

int	execute_single_command(t_minishell *shell, t_command *cmd,
		t_token **token, char **args)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
		return (exec_builtin_command(shell, cmd, token, args));
	return (execute_command(shell, cmd, token, args));
}

int	execute_pipe_sequence(t_minishell *shell, t_command *start_cmd,
		t_token **token, char **args)
{
	int			pipe_count;
	t_pipe_ctx	ctx;

	ctx.token = token;
	ctx.args = args;
	pipe_count = count_pipe_commands(start_cmd);
	if (pipe_count == 1)
		return (execute_single_command(shell, start_cmd, token, args));
	else if (pipe_count == 2)
	{
		ctx.token = token;
		ctx.args = args;
		ft_execute_pipe(shell, start_cmd, start_cmd->next, &ctx);
		return (shell->exit_status);
	}
	else
	{
		ft_execute_multiple_pipes(shell, start_cmd, token, args);
		return (shell->exit_status);
	}
}

int	execute_command_chain(t_minishell *shell, t_command *cmd_list,
		t_token **token, char **args)
{
	t_command	*current;
	int			last_exit_status;

	current = cmd_list;
	last_exit_status = 0;
	while (current)
	{
		if (current->pipe_out)
		{
			last_exit_status = execute_pipe_sequence(shell,
					current, token, args);
			current = skip_pipe_sequence(current);
		}
		else
			last_exit_status = execute_single_command(shell,
					current, token, args);
		shell->exit_status = last_exit_status;
		current = handle_logical_operators(current, last_exit_status);
	}
	return (last_exit_status);
}
