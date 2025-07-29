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

