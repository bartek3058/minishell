#include "../includes/minishell.h"

void    parser_unset(t_token **token, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (is_valid_varname(args[i]))
            add_token(token, args[i], NULL);
        else
            printf("unset: '%s': not a valid identifier\n", args[i]);
        i++;
    }
}

void add_token(t_token **head, char *key, char *value)
{
	t_token *new_token;
	int key_len;

	key_len = ft_strlen("export_") + ft_strlen(key) + 1;
	new_token = malloc(sizeof(t_token));
	if(!new_token)
		return ;
	new_token->type = malloc(key_len);
	if(!new_token->type)
	{	
		return ;
	}
	ft_strcpy(new_token->type, "export_");
	ft_strcat(new_token->type, key);
	if (!value)
		new_token->value = NULL;
	else
		new_token->value = value;
	new_token->next = *head;
	*head = new_token;
}

int	is_valid_varname(const char *str)
{
	int i;

	i = 1;
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
	}
	return 1;
}

void	parser_export(t_token **head, char **args)
{
	int	i;
	char	*eq;
	
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			*eq = '\0';
			if(is_valid_varname(args[i]))
				add_token(head, args[i], eq + 1);
			else
				printf("export: '%s': not valid identifier\n", args[i]);
		}
		else
		{
			if (is_valid_varname(args[i]))
				add_token(head, args[i], NULL);
			else
				printf("export: '%s' :not a valid indentifier\n", args[i]);
		}
		i++;
	}
}

void	parser_cd(t_token **head, char **args)
{
	t_token *new_token;
	t_token *temp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = "cd";
    if(args[1])
	    new_token->value = args[1];
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