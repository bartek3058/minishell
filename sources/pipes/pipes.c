#include "../../includes/minishell.h"

void	ft_pipe_child(int pipefd[2], int is_first_cmd, t_command *cmd, char **envp)
{
	char	*path;
	
	// first: pipe redirections
	ft_pipe_redirection(pipefd, is_first_cmd);
	// then: file redirections
	if (setup_redirections(cmd) < 0)
		exit(1);
	// builtins in pipe:
	if (is_builtin(cmd->args[0]))
	{
		ft_builtins(NULL, cmd->args);
		exit(0);
	}
	// last: external commands
	path = check_path(cmd->args[0]);
	if (!path)
	{
		perror("command not found");
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	ft_execute_pipe(t_minishell *shell, t_command *cmd1, t_command *cmd2)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	char	**envp;

	envp = conv_env_to_array(shell->env_list);
	if (pipe(pipefd) < 0){
		perror("pipe");
		return;
	}
	pid1 = fork();
	if (pid1 == 0)
		ft_pipe_child(pipefd, 1, cmd1, envp);
	pid2 = fork();
	if (pid2 == 0)
		ft_pipe_child(pipefd, 0, cmd2, envp);
	ft_close_pipes(pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
	free_args(envp);
}


void	ft_execute_multiple_pipes(t_minishell *shell, t_command *start_cmd)
{
	int		pipe_count;
	int		**pipes;
	pid_t	*pids;

	pipe_count = count_pipe_commands(start_cmd);
	// Create pipes
	pipes = create_pipes(pipe_count);
	if (!pipes)
		return;
	pids = fork_all_processes(start_cmd, pipes, pipe_count, shell);
	if (!pids){
		free_pipes(pipes, pipe_count);
		return;
	}
	close_all_pipes(pipes, pipe_count);
	wait_for_children(pids, pipe_count, shell);
	free_pipes(pipes, pipe_count);
	free(pids);
}