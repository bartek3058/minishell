#include "../includes/minishell.h"


static void close_all_pipes(int **pipes, int pipe_count)
{
	int	i;
	
	i = 0;
	while (i < pipe_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
static void	ft_close_pipes(int *pipefd)
{
    close(pipefd[0]);
    close(pipefd[1]);
}


static int count_pipe_commands(t_command *start_cmd)
{
	t_command	*current;
	int			count;

	current = start_cmd;
	count = 0;
	while (current && current->pipe_out)
	{
		count++;
		current = current->next;
	}
	count++; // Add final command
	return (count);
}

static int	**create_pipes(int pipe_count)
{
	int		**pipes;
	int		i;

	pipes = malloc(sizeof(int *) * pipe_count - 1);
	if (!pipes)
		return(0);
	i = 0;
	while (i < pipe_count - 1){
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0){
			perror("pipe");
			return(0);
		}
		i++;
	}
	return(pipes);
}

static void		free_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count - 1){
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
// Process setup functions
static void setup_pipe_redirections(int **pipes, int cmd_index, int pipe_count)
{
	// Setup input redirection
	if (cmd_index > 0) // Not first command
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	// Setup output redirection
	if (cmd_index < pipe_count - 1) // Not last command
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	close_all_pipes(pipes, pipe_count);
}

static void	execute_child_command(t_command *cmd, t_minishell *shell)
{
	char	*path;
	char	**envp;

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

static pid_t	*fork_all_processes(t_command *start_cmd, int **pipes, int pipe_count, t_minishell *shell)
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

static void		wait_for_children(pid_t *pids, int pipe_count, t_minishell *shell)
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

static void	ft_pipe_redirection(int *pipefd, int is_first_cmd)
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

static void	ft_pipe_child(int pipefd[2], int is_first_cmd, t_command *cmd, char **envp)
{
    ft_pipe_redirection(pipefd, is_first_cmd);
    char *path = check_path(cmd->args[0]);
    if (path)
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