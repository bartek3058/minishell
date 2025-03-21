#include "../includes/minishell.h"

int	check_path(char *str)
{
	if(access(str, F_OK) != 0)
	{
		printf("cd: invalid %s path", str);
		return 0;
	}
	if(access(str, X_OK) != 0)
	{
		printf("cd: No permission %s path", str);
		return 0;
	}
	return 1;
}

void	parser_cd(t_token **head, char *args)
{
	t_token *new_token;
	t_token *temp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	if(check_path(args[1] == 1))
	{
	new_token->type = "redirect_double_input";
	new_token->value = args[1];
	new_token->next = NULL;
	}
	else
		return ;
	if(*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while(temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	free(temp);
}
