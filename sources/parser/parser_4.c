/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:38:04 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 12:21:09 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_command_node(t_command **cmd_list, t_command **current_cmd,
		t_command **last_cmd)
{
	*current_cmd = create_new_command();
	if (!*cmd_list)
		*cmd_list = *current_cmd;
	else
		(*last_cmd)->next = *current_cmd;
}

void	handle_pipe_token(t_command **current_cmd, t_command **last_cmd,
		t_token **token)
{
	(*current_cmd)->pipe_out = 1;
	*last_cmd = *current_cmd;
	*current_cmd = NULL;
	*token = (*token)->next;
}

void	handle_operator_and_reset(t_command **current_cmd, t_command **last_cmd,
		t_token **token)
{
	*token = handle_operator_token(*current_cmd, *token);
	*last_cmd = *current_cmd;
	*current_cmd = NULL;
}
