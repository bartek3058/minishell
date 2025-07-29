#include "../../includes/minishell.h"

// Process setup functions
void setup_pipe_redirections(int **pipes, int cmd_index, int pipe_count)
{
	// Setup input redirection
	if (cmd_index > 0) // Not first command
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	// Setup output redirection
	if (cmd_index < pipe_count - 1) // Not last command
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	close_all_pipes(pipes, pipe_count);
}

void	execute_child_command(t_command *cmd, t_minishell *shell)
{
	char	*path;
	char	**envp;

	if (setup_redirections(cmd) < 0)
		exit(1);
	envp = conv_env_to_array(shell->env_list);
	if (is_builtin(cmd->args[0])){
		ft_builtins(shell, cmd->args);
		exit(shell->exit_status);
	}
	path = check_path(cmd->args[0]);
	if(path){
		execve(path, cmd->args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return_error("pipe", cmd->args[0], "command not found");
	exit(127);
}


// Process managememnt functions

pid_t	*fork_all_processes(t_command *start_cmd, int **pipes, int pipe_count, t_minishell *shell)
{
	pid_t		*pids;
	t_command	*current;
	int			i;

	pids = malloc(sizeof(pid_t) * pipe_count);
	if (!pids)
		return (NULL);
	current = start_cmd;
	i = 0;
	while (i < pipe_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_pipe_redirections(pipes, i, pipe_count);
			execute_child_command(current, shell);
		}
		current = current->next;
		i++;
	}
	return (pids);
}

void		wait_for_children(pid_t *pids, int pipe_count, t_minishell *shell)
{
	int status;
	int i;

	i = 0;
	while (i < pipe_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == pipe_count - 1) // Last command's exit status
			shell->exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	ft_pipe_redirection(int *pipefd, int is_first_cmd)
{
    if (is_first_cmd)
    {
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]); // Close write end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
    }
}