#include "../includes/minishell.h"

char *redirect_double_input_helper(char **argv)
{
	int	i;

	i = 0;
	
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<<") == 0)
		{
			if (argv[i + 1])
				return ft_strdup(argv[i + 1]);
			else
				return NULL;
		}
		i++;
	}
	return NULL;
}

void	parser_double_redirect_input(t_token **head, char **argv)
{
	t_token *new_token;
	t_token *temp;
	char	*filename;

	filename = redirect_double_output_helper(argv);
	if(!filename)
		printf("Wrong filename !\n");
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = ft_strdup("redirect_double_input");
	new_token->value = filename;
	new_token->next = NULL;
	if(*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while(temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

char *redirect_double_output_helper(char **argv)
{
	int	i;

	i = 0;
	
	while (argv[i])
	{
		if (ft_strcmp(argv[i], ">>") == 0)
		{
			if (argv[i + 1])
				return ft_strdup(argv[i + 1]);
			else
				return NULL;
		}
		i++;
	}
	return NULL;
}

void	parser_double_redirect_output(t_token **head, char **argv)
{
	t_token *new_token;
	t_token *temp;
	char	*filename;

	filename = redirect_double_output_helper(argv);
	if(!filename)
		printf("Wrong filename !\n");
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = ft_strdup("redirect_double_output");
	new_token->value = filename;
	new_token->next = NULL;
	if(*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while(temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}