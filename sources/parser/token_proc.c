#include "../includes/minishell.h"

t_command *create_new_command(void)
{
    t_command *cmd;
    
    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->input_file = NULL;
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
static t_token *handle_pipe_operator(t_command *current_cmd, t_token *token)
{
    current_cmd->pipe_out = 1;
    current_cmd->next = create_new_command();
    return token->next;
}

static t_token *handle_logical_and(t_command *current_cmd, t_token *token)
{
    current_cmd->logical_op = 1; // AND
    current_cmd->next = create_new_command();
    return token->next;
}

static t_token *handle_logical_or(t_command *current_cmd, t_token *token)
{
    current_cmd->logical_op = 2; // OR
    current_cmd->next = create_new_command();
    return token->next;
}

static void add_args_to_command(t_command *cmd, t_token **token, t_minishell *shell)
{
    int 	arg_count;
    t_token	*current;
	int		i;

	arg_count = 0;
	current = *token;
    // Count arguments correctly
    while (current && current->type && 
			(ft_strcmp(current->type, "WORD") == 0 || 
			ft_strcmp(current->type, "VAR_WORD") == 0 ||
			is_builtin(current->type))){
        if ((ft_strcmp(current->type, "WORD") == 0 ||
			ft_strcmp(current->type, "VAR_WORD") == 0) && current->value)
            arg_count++;
        else if (is_builtin(current->type))
            arg_count++;
        current = current->next;
    }
    // Allocate and fill
    cmd->args = malloc(sizeof(char *) * (arg_count + 1));
    if (!cmd->args)
        return;
    current = *token;
    i = 0;
    while (current && current->type && 
			(ft_strcmp(current->type, "WORD") == 0 || 
			ft_strcmp(current->type, "VAR_WORD") == 0 ||
			is_builtin(current->type))){
        if (ft_strcmp(current->type, "WORD") == 0 && current->value)
            cmd->args[i++] = ft_strdup(current->value);
		else if (ft_strcmp(current->type, "VAR_WORD") == 0 && current->value)
				cmd->args[i++] = expand_variables(current->value, shell);
        else if (is_builtin(current->type))
            cmd->args[i++] = ft_strdup(current->type);
        current = current->next;
    }
    cmd->args[i] = NULL;
    *token = current;
}
static void handle_redirection(t_command *cmd, t_token **token)
{
    t_token *current = *token;
    
    if (!current || !current->type)
        return;
    if (ft_strcmp(current->type, ">") == 0 && current->next){
        cmd->output_file = ft_strdup(current->next->value);
        *token = current->next->next;
    }
    else if (ft_strcmp(current->type, "<") == 0 && current->next){
        cmd->input_file = ft_strdup(current->next->value);
        *token = current->next->next;
    }
    else if (ft_strcmp(current->type, ">>") == 0 && current->next){
        cmd->append_file = ft_strdup(current->next->value);
        *token = current->next->next;
    }
    else if (ft_strcmp(current->type, "<<") == 0 && current->next){
        cmd->heredoc = ft_strdup(current->next->value);
        *token = current->next->next;
    }
    else
        *token = current->next;
}
// Token Processing Helper Functions
static t_token *handle_command_token(t_command *cmd, t_token *token, t_minishell *shell)
{
    add_args_to_command(cmd, &token, shell);
    return token;
}
static t_token *handle_redirection_token(t_command *cmd, t_token *token)
{
    handle_redirection(cmd, &token);
    return token;
}
static t_token *handle_operator_token(t_command *current_cmd, t_token *token)
{
    if (ft_strcmp(token->type, "|") == 0)
        return handle_pipe_operator(current_cmd, token);
    else if (ft_strcmp(token->type, "&&") == 0)
        return handle_logical_and(current_cmd, token);
    else if (ft_strcmp(token->type, "||") == 0)
        return handle_logical_or(current_cmd, token);
    
    return token->next;
}
static int is_command_token(t_token *token)
{
    if (!token || !token->type)
        return 0;
    return (ft_strcmp(token->type, "WORD") == 0 ||
			ft_strcmp(token->type, "VAR_WORD") == 0 ||
			is_builtin(token->type));
}

static int is_redirection_token(t_token *token)
{
    if (!token || !token->type)
        return 0;
    return (ft_strcmp(token->type, ">") == 0 || 
            ft_strcmp(token->type, "<") == 0 ||
            ft_strcmp(token->type, ">>") == 0 || 
            ft_strcmp(token->type, "<<") == 0);
}

static int is_operator_token(t_token *token)
{
    if (!token || !token->type)
        return 0;
    return (ft_strcmp(token->type, "|") == 0 || 
            ft_strcmp(token->type, "&&") == 0 ||
            ft_strcmp(token->type, "||") == 0);
}
static t_token *process_single_token(t_command *current_cmd, t_token *token, t_minishell *shell)
{
    if (is_command_token(token))
        return handle_command_token(current_cmd, token, shell);
    else if (is_redirection_token(token))
        return handle_redirection_token(current_cmd, token);
    else if (is_operator_token(token))
        return handle_operator_token(current_cmd, token);
    else
        return token->next;
}

t_command *parse_command_chain(t_token *tokens, t_minishell *shell)
{
    t_command *cmd_list = NULL;
    t_command *current_cmd = NULL;
    t_token *token = tokens;
    
    while (token)
    {
        if (!current_cmd)
        {
            current_cmd = create_new_command();
            if (!cmd_list)
                cmd_list = current_cmd;
        }
        token = process_single_token(current_cmd, token, shell);
        if (!token)
            break;
    }
    return cmd_list;
}