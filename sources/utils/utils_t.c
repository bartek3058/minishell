#include "../../includes/minishell.h"

char	*check_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return full_path;
		free(full_path);
		i++;
	}
	return(0);
}
static int	is_builtin(char *cmd)
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
int	execute_cmd(char *path, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, NULL) == -1)
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
int	execute_command(t_minishell *shell, t_command *cmd)
{
    // Check if command is a builtin
    if (is_builtin(cmd->args[0]))
    {
        // Execute builtin in current process
        ft_builtins(shell, cmd->args);
		return (0);
    }
    else
    {
        // Execute external command
        char *path = check_path(cmd->args[0]);
        if (path)
            execute_cmd(path, cmd->args);
        else
        {
            fprintf(stderr, "Command not found: %s\n", cmd->args[0]);
            return 127; // Command not found exit status
        }
    }
    return 0;
}