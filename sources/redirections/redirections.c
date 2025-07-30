/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:04:20 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/29 19:04:33 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_output_redirection(t_command *cmd)
{
	int	fd;

	if (!cmd->output_files || cmd->output_file_count == 0)
		return (0);
	if (open_and_truncate_outputs(cmd, &fd) < 0)
		return (-1);
	if (dup_last_output(fd) < 0)
		return (-1);
	return (0);
}

void	ft_heredoc_redirection(t_command *cmd)
{
	if (!cmd->heredoc)
		return ;
	write_heredoc_to_tmp(cmd->heredoc);
	redirect_heredoc_input();
}

int	ft_input_redirection(t_command *cmd)
{
	int	fd;

	fd = -1;
	if (!cmd->input_files || cmd->input_file_count == 0)
		return (0);
	if (open_all_input_files(cmd, &fd) < 0)
		return (-1);
	if (dup_last_input(fd) < 0)
		return (-1);
	return (0);
}

int	ft_append_redirection(t_command *cmd)
{
	int	fd;

	if (!cmd->append_files || cmd->append_file_count == 0)
		return (0);
	if (open_all_append_files(cmd, &fd) < 0)
		return (-1);
	return (dup_last_append_fd(fd));
}
