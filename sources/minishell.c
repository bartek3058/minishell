/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomek <tomek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:39:34 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/31 23:04:31 by tomek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_loop_helper(t_minishell *shell, char **args, t_token **token)
{
	t_command	*cmd_list;

	if (shell->line[0] == '\0')
	{
		free(shell->line);
		return ;
	}
	add_history(shell->line);
	args = smart_split(shell->line);
	tokenize_input(args, token);
	cmd_list = parse_command_chain(*token, shell);
	if (!cmd_list)
	{
		cleanup_and_return(args, shell->line, *token);
		return ;
	}
	shell->exit_status = execute_command_chain(shell, cmd_list, token, args);
	free_command_list(cmd_list);
	cleanup_and_return(args, shell->line, *token);
	*token = NULL;
}

void	minishell_loop(t_minishell *shell, char **args, t_token **token)
{
	while (shell->running)
	{
		shell->line = readline("minishell$ ");
		if (shell->line == NULL)
		{
			ft_putstr_fd("\n", 1);
			free_env(shell->env_list);
			exit(shell->exit_status);
		}
		minishell_loop_helper(shell, args, token);
	}
	free_env(shell->env_list);
	shell->env_list = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_token		*token;
	char		**args;

	args = NULL;
	token = NULL;
	(void)argv;
	(void)(argc);
	init_minishell(&shell, envp, &token);
	minishell_loop(&shell, args, &token);
	free_env(shell.env_list);
	return (0);
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*current;
	t_command	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		if (current->args)
			free_args(current->args);
		if (current->input_files)
			free_input_files(current);
		if (current->output_files)
			free_output_files(current);
		if (current->append_files)
			free_append_files(current);
		if (current->heredoc)
			free(current->heredoc);
		free(current);
		current = next;
	}
}
