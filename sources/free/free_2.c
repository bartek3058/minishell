/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:33:39 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 10:55:27 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_command_list_2(t_command *cmd_list)
{
	t_command	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		free_str_array(cmd_list->args);
		free_str_array(cmd_list->input_files);
		free_str_array(cmd_list->output_files);
		free_str_array(cmd_list->append_files);
		if (cmd_list->heredoc)
			free(cmd_list->heredoc);
		if (cmd_list->pipe_fd[0] > 0)
			close(cmd_list->pipe_fd[0]);
		if (cmd_list->pipe_fd[1] > 0)
			close(cmd_list->pipe_fd[1]);
		free(cmd_list);
		cmd_list = tmp;
	}
}
