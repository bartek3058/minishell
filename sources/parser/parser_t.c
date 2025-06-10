#include "../includes/minishell.h"

void parser_single(t_token **token, char **args, int *i)
{
    // Add command token only
    add_token(token, args[*i], NULL);
    // No increment adjustment needed since there are no arguments
}

void parser_multi(t_token **token, char **args, int *i)
{
	char	*command;

    command = args[*i]; // Add command token (first argument as type)
	add_token(token, command, NULL);
    (*i)++;
    while (args[*i] && !is_redirect_or_pipe(args[*i])) // Add all subsequent arguments until we hit a special operator
    {
        if (ft_strcmp(command, "export") == 0 || ft_strcmp(command, "unset") == 0)
        {
            if (is_valid_var_or_assign(args[*i]))
                add_token(token, NULL, args[*i]);
            else
                printf("'%s': not a valid identifier\n", args[*i]);
        }
		else if (ft_strcmp(command, "echo") == 0)
			add_token(token, NULL, strip_quotes(args[*i]));
		else
			add_token(token, NULL, args[*i]);
		(*i)++;
    }
    (*i)--; // Adjust for main parser loop increment
}

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
	if (*head == NULL)
		*head = new_token;
	else {
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}