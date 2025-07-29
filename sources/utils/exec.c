#include "../../includes/minishell.h"
t_command *handle_and_operator(t_command *current, int exit_status)
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

t_command *handle_or_operator(t_command *current, int exit_status)
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
t_command *handle_logical_operators(t_command *current, int exit_status)
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
t_command *skip_pipe_sequence(t_command *current)
{
	while (current && current->pipe_out)
		current = current->next;
	if (current)
		current = current->next;
	return current;
}

int	setup_redirections(t_command *cmd)
{
	if (!cmd)
		return 0;
	if (cmd->input_files && cmd->input_file_count > 0)
	{
		//DEBUG
		// printf("Getting to ft_input redirection\n");
		//END DEBUG	
		if (ft_input_redirection(cmd) < 0)
			return -1;
	}
	if (cmd->heredoc)
		ft_heredoc_redirection(cmd);
	if (cmd->output_files && cmd->output_file_count > 0)
	{
		if (ft_output_redirection(cmd) < 0)
			return (-1);
	}
	if (cmd->append_files && cmd->append_file_count > 0)
	{
		if (ft_append_redirection(cmd) < 0)
			return (-1);
	}
	return 0;
}