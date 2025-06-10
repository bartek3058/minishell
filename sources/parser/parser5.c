#include "../../includes/minishell.h"

void    parser_and(t_token **head)
{
    t_token *new_token;
    t_token *temp;

	new_token = malloc(sizeof(t_token));	
    if (!new_token)
        return ;
    new_token->type = ft_strdup("&&");
    new_token->value = NULL;
    new_token->next = NULL;
    if (*head == NULL)
        *head = new_token;
    else
    {
        temp = *head;
        while(temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
}

void    parser_or(t_token **head)
{
    t_token *new_token;
    t_token *temp;

	new_token = malloc(sizeof(t_token));
    if (!new_token)
        return ;
    new_token->type = ft_strdup("||");
    new_token->value = NULL;
    new_token->next = NULL;
    if (*head == NULL)
        *head = new_token;
    else
    {
        temp = *head;
        while(temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
}
