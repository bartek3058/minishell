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

// static int count_pipe_commands(t_command *start_cmd)
// {
//     t_command *current = start_cmd;
//     int count = 0;
    
//     while (current && current->pipe_out)
//     {
//         count++;
//         current = current->next;
//     }
//     count++; // Add final command
    
//     return count;
// }
static void setup_redirections(t_command *cmd)
{
    if (cmd->input_file)
        ft_input_redirection(cmd);
    else if (cmd->heredoc)
        ft_heredoc_redirection(cmd);
        
    if (cmd->append_file)
        ft_append_redirection(cmd);
    else if (cmd->output_file)
        ft_output_redirection(cmd);
}

static int execute_single_command(t_minishell *shell, t_command *cmd)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return 1;
    
    // Setup redirections
    setup_redirections(cmd);
    
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
// static void setup_pipe_redirections(int pipes[][2], int cmd_index, int pipe_count)
// {
//     // Setup input redirection
//     if (cmd_index > 0) // Not first command
//     {
//         dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
// 		close(pipes[cmd_index - 1][0]);
//     }
    
//     // Setup output redirection  
//     if (cmd_index < pipe_count - 1) // Not last command
//     {
//         dup2(pipes[cmd_index][1], STDOUT_FILENO);
// 		close(pipes[cmd_index][1]);
//     }
    
//     // Close all other pipe file descriptors
//     for (int i = 0; i < pipe_count - 1; i++)
//     {
//         if (i != cmd_index - 1)
// 			close(pipes[i][0]);
//         if (i != cmd_index)
// 			close(pipes[i][1]);
//     }
// }
// static void close_all_pipes(int pipes[][2], int pipe_count)
// {
//     for (int i = 0; i < pipe_count; i++)
//     {
//         close(pipes[i][0]);
//         close(pipes[i][1]);
//     }
// }
// static int wait_for_children(pid_t *pids, int count)
// {
//     int status = 0;
//     int last_status = 0;
    
//     for (int i = 0; i < count; i++)
//     {
//         waitpid(pids[i], &status, 0);
//         if (i == count - 1) // Last command's exit status
//             last_status = WEXITSTATUS(status);
//     }
    
//     return last_status;
// }
static int execute_pipe_sequence(t_minishell *shell, t_command *start_cmd)
{
	t_command	*cmd1;
	t_command	*cmd2;

	cmd1 = start_cmd;
	cmd2 = start_cmd->next;
	//for now, let's handle only 2-command pipes to debug
	if(!cmd2)
		return execute_single_command(shell, cmd1);
	ft_execute_pipe(shell, cmd1, cmd2);
	return shell->exit_status;
}

int execute_command_chain(t_minishell *shell, t_command *cmd_list)
{
	t_command *current = cmd_list;
	int last_exit_status = 0;

	while (current)
	{
		if (current->pipe_out)
		{
			last_exit_status = execute_pipe_sequence(shell, current);
			current = skip_pipe_sequence(current);
		}
		else
		{
			last_exit_status = execute_single_command(shell, current);
		}

		shell->exit_status = last_exit_status;
		current = handle_logical_operators(current, last_exit_status);
	}

	return last_exit_status;
}