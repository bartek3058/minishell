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