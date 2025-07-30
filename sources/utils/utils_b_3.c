/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:12:34 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 17:03:13 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process_exec(char *path, char **args, char **envp)
{
	if (execve(path, args, envp) == -1)
	{
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}

char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static int	fork_and_execute(t_minishell *shell, t_command *cmd, t_token **token, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execute_child_process(shell, cmd, token, args);
		exit (1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	else
	{
		perror("fork");
		return (1);
	}
}

int	execute_command(t_minishell *shell, t_command *cmd, t_token **token, char **args)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		ft_builtins(shell, cmd->args, cmd, token, args);
		return (shell->exit_status);
	}
	return (fork_and_execute(shell, cmd, token, args));
}

int	return_error(char *origin, char *identifier, char *message)
{
	ft_putstr_fd(origin, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
