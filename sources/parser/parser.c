#include "../includes/minishell.h"

int count_echo_len(char **argv, int i)
{
    int len = 0;

    while (argv[i] && !is_redirect_or_pipe(argv[i]))
        len += ft_strlen(argv[i++]) + 1;
    return len;
}

char *build_echo_value(char **argv)
{
	int		i;
	int		j;
	int		len;
	char	*result;
	char	*tmp;

	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		i = 2;
	else
		i = 1;

	// Calculate length after stripping quotes
    for (j = i; argv[j] && !is_redirect_or_pipe(argv[j]); j++) {
        tmp = strip_quotes(argv[j]);
        len += ft_strlen(tmp) + 1;
        free(tmp);
    }

    result = malloc(len + 1);
    if (!result)
        return NULL;

    result[0] = '\0';

    while (argv[i] && !is_redirect_or_pipe(argv[i]))
    {
		tmp = strip_quotes(argv[i]);
		ft_strcat(result, tmp);
		free(tmp);
        if (argv[i + 1] && !is_redirect_or_pipe(argv[i + 1]))
            ft_strcat(result, " ");
        i++;
    }

    return result;
}

void parser_echo(t_token **head, char **argv)
{
    int i = 1;
    t_token *new_token, *temp;

    // First token: command only
    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return;
    new_token->type = ft_strdup("echo");
    new_token->value = NULL;
    new_token->next = NULL;

    if (*head == NULL)
        *head = new_token;
    else
    {
        temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
    temp = new_token;

    // Add each argument as a separate token
    while (argv[i] && !is_redirect_or_pipe(argv[i]))
    {
        t_token *arg_token = malloc(sizeof(t_token));
        if (!arg_token)
            return;
        arg_token->type = NULL;
        arg_token->value = strip_quotes(argv[i]);
        arg_token->next = NULL;
        temp->next = arg_token;
        temp = arg_token;
        i++;
    }
}

void    parser_pwd(t_token **head)
{
    t_token *new_token = malloc(sizeof(t_token));
    t_token *temp;
    if (!new_token)
        return ;
    new_token->type = ft_strdup("pwd");
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

void    parser(char **args, t_token **token)
{
    int i;
    i = 0;
    while(args[i] != NULL)
    {
        if (ft_strcmp(args[i], "pwd") == 0)
            parser_pwd(token);
        else if (ft_strcmp(args[i], "echo") == 0)
            parser_echo(token, args);
        else if (ft_strcmp(args[i], "export") == 0)
		    parser_export(token, args);
	    else if (ft_strcmp(args[i], "unset") == 0)
		    parser_unset(token, args);
	    else if (ft_strcmp(args[i], "env") == 0)
		    parser_env(token, args);
        else if (ft_strcmp(args[i], "cd") == 0){
            parser_cd(token, args, i);
			if (args[i + 1] && !is_redirect_or_pipe(args[i + 1]))
        	i++; // skip the argument so it's not processed again
		}
		else if (ft_strcmp(args[i], "exit") == 0)
			parser_exit(token);
        else
            parser_helper(token, args, &i);
        i++;
    }
}
