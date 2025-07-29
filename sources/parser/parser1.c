#include "../includes/minishell.h"

void add_token(t_token **head, char *type, char *value)
{
	t_token *new_token;
	t_token *temp;

	new_token = malloc(sizeof(t_token));
	if(!new_token)
		return ;
	if (type)
		new_token->type = ft_strdup(type);
	else
		new_token->type = NULL;
	if (value)
		new_token->value = ft_strdup(value);
	else
		new_token->value = NULL;
	new_token->next = NULL;
	//DEBUG here
	//DEBUG
	if (*head == NULL)
		*head = new_token;
	else {
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}
int	skip_spaces(char *str,int i)
{
	while (str[i] == ' ')
		i++;
	return(i);
}
void	handle_redirect_token(t_token **token, char **args, int *i, int redirect_len)
{
	if (redirect_len == 2)
	{
		if (args[*i][0] == '>')
			add_redirection_token(token, args, i, ">>");
		else
			add_redirection_token(token, args, i, "<<");
	}
	else
	{
		if (args[*i][0] == '>')
			add_redirection_token(token, args, i, ">");
		else
			add_redirection_token(token, args, i, "<");
	}
}
int	is_command_token(t_token *token)
{
	if (!token || !token->type)
		return 0;
	return (ft_strcmp(token->type, "WORD") == 0 ||
			ft_strcmp(token->type, "VAR_WORD") == 0 ||
			is_builtin(token->type));
}

int	is_redirection_token(t_token *token)
{
	if (!token || !token->type)
		return 0;
	return (ft_strcmp(token->type, ">") == 0 ||
			ft_strcmp(token->type, "<") == 0 ||
			ft_strcmp(token->type, ">>") == 0 ||
			ft_strcmp(token->type, "<<") == 0);
}
