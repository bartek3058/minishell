#include "../../includes/minishell.h"

static t_command *handle_and_operator(t_command *current, int exit_status)
{
	if (exit_status != 0)
	{
		// Skip next command if current failed
		current = current->next;
		if (current)
			current = current->next;
		return current;
	}
	return current->next;
}

static t_command *handle_or_operator(t_command *current, int exit_status)
{
	if (exit_status == 0)
	{
		// Skip next command if current succeeded
		current = current->next;
		if (current)
			current = current->next;
		return current;
	}
	return current->next;
}

// Logical Operator Handler
static t_command *handle_logical_operators(t_command *current, int exit_status)
{
	if (!current)
		return NULL;

	if (current->logical_op == 1) // &&
		return handle_and_operator(current, exit_status);
	else if (current->logical_op == 2) // ||
		return handle_or_operator(current, exit_status);
	else
		return current->next;
}

// pipe sequence helpers
static t_command *skip_pipe_sequence(t_command *current)
{
	while (current && current->pipe_out)
		current = current->next;
	if (current)
		current = current->next;
	return current;
}

void	setup_redirections(t_command *cmd)
{
	if (!cmd)
		return;
	if (cmd->input_files && cmd->input_file_count > 0)
	{
		//DEBUG
		printf("Getting to ft_input redirection\n");
		//END DEBUG	
		ft_input_redirection(cmd);
	}
	if (cmd->heredoc)
		ft_heredoc_redirection(cmd);
	if (cmd->output_file || cmd->append_file)
		ft_output_redirection(cmd);
}

static int execute_single_command(t_minishell *shell, t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return 1;

	// Check if builtin
	if (is_builtin(cmd->args[0]))
	{
		ft_builtins(shell, cmd->args);
		return shell->exit_status;
	}
	else
	{
		return execute_command(shell, cmd);
	}
}

static int execute_pipe_sequence(t_minishell *shell, t_command *start_cmd)
{
	int			pipe_count;
	t_command	*current;

	pipe_count = 0;
	current = start_cmd;
	// Count commands in pipe sequence
	while (current && current->pipe_out)
	{
		pipe_count++;
		current = current->next;
	}
	pipe_count++; // Add final command

	if (pipe_count == 1)
		return execute_single_command(shell, start_cmd);
	else if (pipe_count == 2)
	{
		// Use existing 2-command pipe function
		ft_execute_pipe(shell, start_cmd, start_cmd->next);
		return shell->exit_status;
	}
	else
	{
		// Use new multiple pipe function
		ft_execute_multiple_pipes(shell, start_cmd);
		return shell->exit_status;
	}
}


int execute_command_chain(t_minishell *shell, t_command *cmd_list)
{
	t_command *current = cmd_list;
	int last_exit_status = 0;

	while (current)
	{
		if (current->pipe_out){
			last_exit_status = execute_pipe_sequence(shell, current);
			current = skip_pipe_sequence(current);
		}
		else
			last_exit_status = execute_single_command(shell, current);

		shell->exit_status = last_exit_status;
		current = handle_logical_operators(current, last_exit_status);
	}

	return last_exit_status;
}