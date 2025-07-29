#include "../includes/minishell.h"

t_command	*create_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	cmd->args = malloc(sizeof(char *) * 256); // Allocate space for up to 255 args
	if (!cmd->args)
	{
		free(cmd);
		return NULL;
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
	return cmd;
}
// static void add_args_to_command(t_command *cmd, t_token **token, t_minishell *shell)
// {
// 	int		arg_count;
// 	t_token	*current;
// 	t_token	*prev;
// 	int		i;

// 	arg_count = 0;
// 	current = *token;
// 	prev = NULL;

// 	// First pass: Count ONLY actual command arguments
// 	while (current)
// 	{
// 		if(ft_strcmp(current->type, "WORD") == 0 ||
// 			ft_strcmp(current->type, "VAR_WORD") == 0 ||
// 			is_builtin(current->type))
// 		{
// 			if (prev && 
// 				(ft_strcmp(prev->type, "<") == 0 ||
// 				ft_strcmp(prev->type, ">") == 0 ||
// 				ft_strcmp(prev->type, ">>") == 0 ||
// 				ft_strcmp(prev->type, "<<") == 0))
// 					{
// 						//skip this WORD - it's a redirection target
// 					}
// 			else
// 				arg_count++;
// 		}
// 		else if (ft_strcmp(current->type, "|") == 0 ||
// 				ft_strcmp(current->type, "&&") == 0 ||
// 				ft_strcmp(current->type, "||") == 0)
// 					break; //Stop at pipe and logicals - new command starts
// 		prev = current;
// 		current = current->next;
// 	}
// 	// Allocate and fill
// 	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
// 	if (!cmd->args){
// 		free(cmd);
// 		return;
// 	}
// 	// Second pass: collect actual arguments, skip redir targets
// 	current = *token;
// 	prev = NULL;
// 	i = 0;
// 	while (current)
// 	{ 
// 		if (ft_strcmp(current->type, "WORD") == 0 && current->value)
// 		{
// 			if (prev &&
// 				(ft_strcmp(prev->type, "<") == 0 ||
// 				 ft_strcmp(prev->type, ">") == 0 ||
// 				 ft_strcmp(prev->type, ">>") == 0 ||
// 				 ft_strcmp(prev->type, "<<") == 0))
// 			{
// 				// Skip
// 			}
// 			else
// 				cmd->args[i++] = ft_strdup(current->value);
// 		}
// 		else if (ft_strcmp(current->type, "VAR_WORD") == 0 && current->value)
// 		{
// 			if (prev &&
// 				(ft_strcmp(prev->type, "<") == 0 ||
// 				 ft_strcmp(prev->type, ">") == 0 ||
// 				 ft_strcmp(prev->type, ">>") == 0 ||
// 				 ft_strcmp(prev->type, "<<") == 0))
// 			{
// 				// Skip
// 			}
// 			else
// 				cmd->args[i++] = expand_variables(current->value, shell);
// 		}
// 		else if (is_builtin(current->type))
// 			cmd->args[i++] = ft_strdup(current->type);
// 		else if (ft_strcmp(current->type, "|") == 0 ||
// 				 ft_strcmp(current->type, "&&") == 0 ||
// 				 ft_strcmp(current->type, "||") == 0)
// 		{
// 			// Stop at pipe/logical operators
// 			break;
// 		}
// 		prev = current;
// 		current = current->next;
// 	}
// 	cmd->args[i] = NULL;
// 	*token = current;
// 	//DEBUG
// 	printf("DEBUG: Creating command with %d arguments:\n", arg_count);
// 	for (int j = 0; cmd->args[j]; j++)
// 		printf("  arg[%d] = '%s'\n", j, cmd->args[j]);
// 	printf("DEBUG: Input file = '%s'\n", cmd->input_file ? cmd->input_file : "NULL");
// 	printf("DEBUG: Has next command = %s\n", cmd->next ? "YES" : "NO");
// 	//END DEBUG

// }
void	handle_redirection(t_command *cmd, t_token **token)
{
	t_token	*current;

	current = *token;
	if (!current || !current->type)
	{
		*token = NULL;
		return;
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
static t_token	*handle_command_token(t_command *cmd, t_token *token, t_minishell *shell)
{
	//add_args_to_command(cmd, &token, shell);
	//return token;

	// Another approach: Only add the current token as an argument
    int i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	if (i >= 255)
		return token->next;
	if (ft_strcmp(token->type, "WORD") == 0 && token->value)
		cmd->args[i] = strip_quotes(token->value);
	else if (ft_strcmp(token->type, "VAR_WORD") == 0 && token->value)
		cmd->args[i] = expand_variables(token->value, shell);
	else if (is_builtin(token->type))
		cmd->args[i] = strip_quotes(token->type);
	cmd->args[i + 1] = NULL;
	return token->next;
}

// static t_token *process_single_token(t_command *current_cmd, t_token *token, t_minishell *shell)
// {
//     if (is_command_token(token))
//         return handle_command_token(current_cmd, token, shell);
//     else if (is_redirection_token(token))
//         return handle_redirection_token(current_cmd, token);
//     else if (is_operator_token(token))
//         return handle_operator_token(current_cmd, token);
//     else
//         return token->next;
// }

t_command	*parse_command_chain(t_token *tokens, t_minishell *shell)
{
	t_command	*cmd_list = NULL;
	t_command	*current_cmd = NULL;
	t_command	*last_cmd = NULL;
	t_token		*token = tokens;

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
	return cmd_list;
}



