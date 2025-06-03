#include "../includes/minishell.h"

void parser_unset(t_token **token, char **args)
{
    int i;

    add_token(token, "unset", NULL);
    i = 1;
    while (args[i])
    {
        if (is_valid_varname(args[i]))
            add_token(token, NULL, args[i]);
        else
            printf("unset: '%s': not a valid identifier\n", args[i]);
        i++;
    }
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

int	is_valid_varname(const char *str)
{
	int i;

	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return 0;
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
		i++;
	}
	return 1;
}

void parser_export(t_token **head, char **args)
{
    int i;

    add_token(head, "export", NULL);
    i = 1;
    while (args[i])
    {
        printf("export: checking '%s'\n", args[i]);
		if (is_valid_var_or_assign(args[i])){
            add_token(head, NULL, args[i]);
			printf("export: '%s' added\n", args[i]);
		}
        else
            printf("export: '%s': not a valid identifier\n", args[i]);
        i++;
    }
}

void	parser_cd(t_token **head, char **args, int i)
{
	t_token *new_token;
	t_token *temp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = ft_strdup("cd");
    if(args[i + 1] && !is_redirect_or_pipe(args[i + 1]))
	    new_token->value = ft_strdup(args[i + 1]);
    else
    {
        new_token->value = NULL;
    }
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
