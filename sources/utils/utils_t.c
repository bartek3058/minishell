/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:27:16 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 19:07:23 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*result;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	result = search_in_paths(paths, cmd);
	free_args(paths);
	return (result);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_cmd(char *path, char **args, t_env *env_list)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = conv_env_to_array(env_list);
	if (!envp)
	{
		perror("Failed to convert env_list to array");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		child_process_exec(path, args, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	return (0);
}

static void	handle_execve_failure(t_fork_ctx *ctx, t_command *cmd,
			char *path, char **envp)
{
	perror("execve");
	free_command_list(cmd);
	free_env(ctx->shell->env_list);
	free_tokens(*(ctx->token));
	free_args(ctx->args);
	free_args(envp);
	free(path);
	exit(EXIT_FAILURE);
}

void	execute_child_process(t_minishell *shell, t_command *cmd,
	t_token **token, char **args)
{
	char		*path;
	char		**envp;
	t_fork_ctx	ctx;

	ctx.shell = shell;
	ctx.token = token;
	ctx.args = args;
	if (setup_redirections(cmd) < 0)
		exit(1);
	path = check_path(cmd->args[0]);
	if (!path)
	{
		return_error("execute command", cmd->args[0], "command not found");
		free_command_list(cmd);
		free_env(shell->env_list);
		free_tokens(*token);
		free_args(args);
		exit(127);
	}
	envp = conv_env_to_array(shell->env_list);
	if (execve(path, cmd->args, envp) == -1)
		handle_execve_failure(&ctx, cmd, path, envp);
}
