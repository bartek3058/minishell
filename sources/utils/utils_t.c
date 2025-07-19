#include "../../includes/minishell.h"

char	*check_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	if (!cmd || !*cmd)
		return NULL;
	if (ft_strchr(cmd, '/')) // czy ścieżka jest względna czy bezwzględna
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		else
			return NULL;
	}
	path = getenv("PATH");
	if (!path)
		return NULL;
	paths = ft_split(path, ':');
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_args(paths);
			return full_path;
		}
		free(full_path);
		i++;
	}
	free_args(paths);
	return(0);
}
int	is_builtin(char *cmd)
{
    if (!cmd)
        return 0;
    if (ft_strcmp(cmd, "echo") == 0)
        return 1;
    if (ft_strcmp(cmd, "cd") == 0)
        return 1;
    if (ft_strcmp(cmd, "pwd") == 0)
        return 1;
    if (ft_strcmp(cmd, "export") == 0)
        return 1;
    if (ft_strcmp(cmd, "unset") == 0)
        return 1;
    if (ft_strcmp(cmd, "env") == 0)
        return 1;
    if (ft_strcmp(cmd, "exit") == 0)
        return 1;
    return 0;
}
int	execute_cmd(char *path, char **args, t_env *env_list)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = conv_env_to_array(env_list); // Convert env_list to char ** for execve
	if (!envp)
	{
		perror("Failed to convert env_list to array");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
//		printf("DEBUG: execve('%s', ...)\n", path);
		if (execve(path, args, envp) == -1)
		{
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			return WEXITSTATUS(status);  // Return the exit status
	}
	else
	{
		perror("fork erorr");
		exit(EXIT_FAILURE);
	}
	return(0);
}
static void	execute_child_process(t_minishell *shell, t_command *cmd)
{
	char	*path;
	char	**envp;
	
	setup_redirections(cmd);
	path = check_path(cmd->args[0]);
	if (!path)
	{
		return_error("execute command", cmd->args[0], "command not found");
		exit(127); // Command not found exit status
	}
	envp = conv_env_to_array(shell->env_list);
	if(execve(path, cmd->args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}

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