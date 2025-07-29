#include "../../includes/minishell.h"

void child_process_exec(char *path, char **args, char **envp) 
{
	if (execve(path, args, envp) == -1) 
	{
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}

char *search_in_paths(char **paths, char *cmd) 
{
	int i = 0;
	char *tmp;
	char *full_path;

	while (paths && paths[i]) 
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return full_path;
		free(full_path);
		i++;
	}
	return NULL;
}

static int	fork_and_execute(t_minishell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;

	//Fork for external commands
	pid = fork();
	if (pid == 0)
	{
		execute_child_process(shell, cmd);
		exit (1);
	}
		else if (pid > 0)
	{
		// PARENT PROCESS - Wait for child
		waitpid(pid, &status, 0);
		if(WIFEXITED(status))
			return WEXITSTATUS(status);
		return (1);
	}
	else
	{
		perror("fork");
		return (1);
	}
}

int	execute_command(t_minishell *shell, t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return 1;
	// Check if command is a builtin
	if (is_builtin(cmd->args[0]))
	{
		// Execute builtin in current process
		ft_builtins(shell, cmd->args);
		return shell->exit_status;
	}
	return (fork_and_execute(shell, cmd));
}
int return_error(char *origin, char *identifier, char *message)
{
	ft_putstr_fd(origin, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

