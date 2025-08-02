/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:45:19 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 13:13:02 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*create_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * 256);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args[0] = NULL;
	cmd->input_files = malloc(sizeof(char *) * 16);
	cmd->input_file_count = 0;
	cmd->output_files = malloc(sizeof(char *) * 16);
	cmd->output_file_count = 0;
	cmd->append_files = malloc(sizeof(char *) * 16);
	cmd->append_file_count = 0;
	cmd->heredoc = NULL;
	cmd->logical_op = 0;
	cmd->pipe_out = 0;
	cmd->next = NULL;
	cmd->pid = 0;
	return (cmd);
}

void	handle_redirection(t_command *cmd, t_token **token)
{
	t_token	*current;

	current = *token;
	if (!current || !current->type)
	{
		*token = NULL;
		return ;
	}
	if (ft_strcmp(current->type, "<") == 0)
		handle_input_redirection(cmd, token);
	else if (ft_strcmp(current->type, ">") == 0)
		handle_output_redirection(cmd, token);
	else if (ft_strcmp(current->type, ">>") == 0)
		handle_append_redirection(cmd, token);
	else if (ft_strcmp(current->type, "<<") == 0)
		handle_heredoc_redirection(cmd, token);
	else
		*token = current->next;
}

// Token Processing Helper Functions
static t_token	*handle_command_token(t_command *cmd, t_token *token,
		t_minishell *shell)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	if (i >= 255)
		return (token->next);
	if (ft_strcmp(token->type, "WORD") == 0 && token->value)
		cmd->args[i] = strip_quotes(token->value);
	else if (ft_strcmp(token->type, "VAR_WORD") == 0 && token->value)
		cmd->args[i] = expand_variables(token->value, shell);
	else if (is_builtin(token->type))
		cmd->args[i] = strip_quotes(token->type);
	cmd->args[i + 1] = NULL;
	return (token->next);
}

t_command	*parse_command_chain(t_token *tokens, t_minishell *shell)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_command	*last_cmd;
	t_token		*token;

	cmd_list = NULL;
	current_cmd = NULL;
	last_cmd = NULL;
	token = tokens;
	while (token)
	{
		if (!current_cmd)
			init_command_node(&cmd_list, &current_cmd, &last_cmd);
		if (is_redirection_token(token))
			token = handle_redirection_token(current_cmd, token);
		else if (ft_strcmp(token->type, "|") == 0)
			handle_pipe_token(&current_cmd, &last_cmd, &token);
		else if (is_operator_token(token))
			handle_operator_and_reset(&current_cmd, &last_cmd, &token);
		else if (is_command_token(token))
			token = handle_command_token(current_cmd, token, shell);
		else
			token = token->next;
	}
	return (cmd_list);
}
