/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomek <tomek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:07:54 by tomek             #+#    #+#             */
/*   Updated: 2025/07/31 23:07:56 by tomek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_output_files(t_command *cmd_list)
{
	t_command *current;
	int i;
	
	current = cmd_list;
	if (!current->output_files)
		return;
	i=0;
	while (i < current->output_file_count)
		free(current->output_files[i++]);
	free(current->output_files);
}

void	free_input_files(t_command *cmd_list)
{
	t_command *current;
	int i;
	
	current = cmd_list;
	if (!current->input_files)
		return;
	i=0;
	while (i < current->input_file_count)
		free(current->input_files[i++]);
	free(current->input_files);
}

void	free_append_files(t_command *cmd_list)
{
	t_command *current;
	int i;
	
	current = cmd_list;
	if (!current->append_files)
		return;
	i=0;
	while (i < current->append_file_count)
		free(current->append_files[i++]);
	free(current->append_files);
}

