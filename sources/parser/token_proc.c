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
	cmd->output_file = NULL;
	cmd->append_file = NULL;
	cmd->heredoc = NULL;
	cmd->logical_op = 0;
	cmd->pipe_out = 0;
	cmd->next = NULL;
	cmd->pid = 0;
	return cmd;
}

// Operator-Specific Handlers
static t_token	*handle_pipe_operator(t_command *current_cmd, t_token *token)
{
	current_cmd->pipe_out = 1;
	current_cmd->next = create_new_command();
	return token->next;
}

static t_token	*handle_logical_and(t_command *current_cmd, t_token *token)
{
	current_cmd->logical_op = 1; // AND
	current_cmd->next = create_new_command();
	return token->next;
}

static t_token	*handle_logical_or(t_command *current_cmd, t_token *token)
{
	current_cmd->logical_op = 2; // OR
	current_cmd->next = create_new_command();
	return token->next;
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
static void	handle_redirection(t_command *cmd, t_token **token)
{
	t_token	*current;

	current = *token;
	if (!current || !current->type){
		*token = NULL;
		return;
	}
	if (ft_strcmp(current->type, "<") == 0)
	{
		if (current->next && current->next->value)
		{
			//DEBUG
			// printf("Debug from handle_redirections:\n");
			// print_tokens(current);
			//END DEBUG
			//Okazuje się że tutaj nie dobrze uwalniac pamięc
			// if (cmd->input_file)
			// {
			// 	j = 0;
			// 	while (j < cmd->input_file_count)
			// 	{
			// 		free(cmd->input_file[j]);
			// 		j++;
			// 	}
			// 	free(cmd->input_file);
			// 	cmd->input_file_count = 0;
			// }
			cmd->input_files[cmd->input_file_count] = strip_quotes(current->next->value);
			cmd->input_file_count++;
			//DEBUG
			// printf("Input_file: %s\n", cmd->input_file);
			//END DEBUG
			*token = current->next->next;
			//DEBUG
			// printf("Debug from handle_redirections (after), will proceed to the token:\n");
			// print_tokens(*token);
			//END DEBU
		}
		else
			*token = NULL;
	}
	else if (ft_strcmp(current->type, ">") == 0)
	{
		if (current->next && current->next->value)
		{
			if (cmd->output_file)
				free(cmd->output_file);
			cmd->output_file = strip_quotes(current->next->value);
			*token = current->next->next;
		}
		else
			*token = NULL;
	}
	else if (ft_strcmp(current->type, ">>") == 0)
	{
		if (current->next && current->next->value)
		{
			if (cmd->append_file)
				free(cmd->append_file);
			cmd->append_file = strip_quotes(current->next->value);
			*token = current->next->next;
		}
		else
			*token = NULL;
	}
	else if (ft_strcmp(current->type, "<<") == 0)
	{
		if (current->next && current->next->value)
		{
			if(cmd->heredoc)
				free(cmd->heredoc);
			cmd->heredoc = strip_quotes(current->next->value);
			*token = current->next->next;
		}
		else
			*token = NULL;
	}
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
static t_token	*handle_redirection_token(t_command *cmd, t_token *token)
{
	handle_redirection(cmd, &token);
	return token;
}
static t_token	*handle_operator_token(t_command *current_cmd, t_token *token)
{
	if (ft_strcmp(token->type, "|") == 0)
		return handle_pipe_operator(current_cmd, token);
	else if (ft_strcmp(token->type, "&&") == 0)
		return handle_logical_and(current_cmd, token);
	else if (ft_strcmp(token->type, "||") == 0)
		return handle_logical_or(current_cmd, token);

	return token->next;
}
static int	is_command_token(t_token *token)
{
	if (!token || !token->type)
		return 0;
	return (ft_strcmp(token->type, "WORD") == 0 ||
			ft_strcmp(token->type, "VAR_WORD") == 0 ||
			is_builtin(token->type));
}

static int	is_redirection_token(t_token *token)
{
	if (!token || !token->type)
		return 0;
	return (ft_strcmp(token->type, ">") == 0 ||
			ft_strcmp(token->type, "<") == 0 ||
			ft_strcmp(token->type, ">>") == 0 ||
			ft_strcmp(token->type, "<<") == 0);
}

static int	is_operator_token(t_token *token)
{
	if (!token || !token->type)
		return 0;
	return (ft_strcmp(token->type, "|") == 0 ||
			ft_strcmp(token->type, "&&") == 0 ||
			ft_strcmp(token->type, "||") == 0);
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
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_command	*last_cmd;
	t_token		*token;

	cmd_list = NULL;
	current_cmd = NULL;
	last_cmd = NULL;
	token = tokens;
	//DEBUG
	// printf ("Printing list of tokens: \n");
	// while (token){
	// 	print_tokens(token);
	// 	token=token->next;
	// }
	//END DEBUG

	while (token)
	{
		if (!current_cmd)
		{
			current_cmd = create_new_command();
			if (!cmd_list)
				cmd_list = current_cmd;
			else
				last_cmd->next = current_cmd;
		}

		//process tokens for current command
		//DEBUG
		// if (ft_strcmp(token->type, "<") == 0 || ft_strcmp(token->type, ">") == 0)
		// 	printf("Check if redir: YES\n");
		// else
		// 	printf("Check if redir: NO\n");
		//END DEBUG
		if (!token)
			break;

		if (is_redirection_token(token)){
			//DEBUG
			// printf("Redir token found! type='%s', value='%s'\n", token->type, token->value);
			//END DEBUG
			token = handle_redirection_token(current_cmd, token);
			//DEBUG
			// printf("After redirection, next token type='%s', value='%s'\n", token ? token->type : "NULL", token ? token->value : "NULL");
			//END DEBUG
		}
		else if (ft_strcmp(token->type, "|") == 0){
			//Finalize current command and prepare for next
			current_cmd->pipe_out = 1;
			last_cmd = current_cmd;
			current_cmd = NULL; // Force creation of new command
			token = token->next;
		}
		else if (is_operator_token(token)){
			//DEBUG
			// printf("Operator token found!\n");
			// END DEBUG
			token = handle_operator_token(current_cmd, token);
			last_cmd = current_cmd;
			current_cmd = NULL;
		}
		else if (is_command_token(token)){
			//DEBUG
			// printf("Command token found!\n");
			// END DEBUG
			token = handle_command_token(current_cmd, token, shell);

		}
		else
			token = token->next;
	}
	return cmd_list;
}