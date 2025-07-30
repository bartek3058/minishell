/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:35:03 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/29 18:52:22 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_logical_or(t_command *current_cmd, t_token *token)
{
	current_cmd->logical_op = 2;
	current_cmd->next = create_new_command();
	return (token->next);
}

void	handle_input_redirection(t_command *cmd, t_token **token)
{
	t_token	*current;

	current = *token;
	if (current->next && current->next->value)
	{
		cmd->input_files[cmd->input_file_count]
			= strip_quotes(current->next->value);
		cmd->input_file_count++;
		*token = current->next->next;
	}
	else
		*token = NULL;
}

void	handle_output_redirection(t_command *cmd, t_token **token)
{
	t_token	*current;

	current = *token;
	if (current->next && current->next->value)
	{
		cmd->output_files[cmd->output_file_count]
			= strip_quotes(current->next->value);
		cmd->output_file_count++;
		*token = current->next->next;
	}
	else
		*token = NULL;
}

void	handle_append_redirection(t_command *cmd, t_token **token)
{
	t_token	*current;

	current = *token;
	if (current->next && current->next->value)
	{
		cmd->append_files[cmd->append_file_count]
			= strip_quotes(current->next->value);
		cmd->append_file_count++;
		*token = current->next->next;
	}
	else
		*token = NULL;
}

void	handle_heredoc_redirection(t_command *cmd, t_token **token)
{
	t_token	*current;

	current = *token;
	if (current->next && current->next->value)
	{
		if (cmd->heredoc)
			free(cmd->heredoc);
		cmd->heredoc = strip_quotes(current->next->value);
		*token = current->next->next;
	}
	else
		*token = NULL;
}
