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

//static void	free_string_array(char **arr, int count)
//{
//	int	i;

//	if (!arr)
//		return;
//	i = 0;
//	while (i < count && arr[i])
//	{
//		free(arr[i]);
//		i++;
//	}
//	free(arr);
//}

//static void	free_args(char **args)
//{
//	int	i;

//	if (!args)
//		return;
//	for (i = 0; args[i]; i++)
//		free(args[i]);
//	free(args);
//}
//void	free_command(t_command *cmd)
//{
//	if (!cmd)
//		return;
//	free_args(cmd->args);
//	free_string_array(cmd->input_files, cmd->input_file_count);
//	free_string_array(cmd->output_files, cmd->output_file_count);
//	free_string_array(cmd->append_files, cmd->append_file_count);
//	if (cmd->heredoc)
//		free(cmd->heredoc);
//	free(cmd);
//}
//void	free_command_list_2(t_command *cmd)
//{
//	t_command *tmp;

//	while (cmd)
//	{
//		tmp = cmd->next;
//		free_command(cmd);
//		cmd = tmp;
//	}
//}

#include <stdlib.h>
#include <unistd.h> // dla close()

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return;
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

		// Zamykamy deskryptory potoku jeśli otwarte
		if (cmd_list->pipe_fd[0] > 0)
			close(cmd_list->pipe_fd[0]);
		if (cmd_list->pipe_fd[1] > 0)
			close(cmd_list->pipe_fd[1]);

		free(cmd_list);
		cmd_list = tmp;
	}
}
