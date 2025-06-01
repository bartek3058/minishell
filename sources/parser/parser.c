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
    int i;
    int len;
    char *result;

    if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
        i = 2;
    else
        i = 1;
    len = count_echo_len(argv, i);
    result = malloc(len + 1);
    if (!result)
        return NULL;

    result[0] = '\0';

    while (argv[i] && !is_redirect_or_pipe(argv[i]))
    {
        ft_strcat(result, argv[i]);
        if (argv[i + 1] && !is_redirect_or_pipe(argv[i + 1]))
            ft_strcat(result, " ");
        i++;
    }

    return result;
}

void    parser_echo(t_token **head, char **argv)
{
    t_token *new_token;
    t_token *temp;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return;

    if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
        new_token->type = "echo_n";
    else
        new_token->type = "echo";

    new_token->value = build_echo_value(argv);
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
}

void    parser_pwd(t_token **head)
{
    t_token *new_token = malloc(sizeof(t_token));
    t_token *temp;
    if (!new_token)
        return ;
    new_token->type = "pwd";
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
        else if (ft_strcmp(args[i], "cd") == 0)
            parser_cd(token, args, i);
        else
            parser_helper(token, args, &i);
        i++;
    }
}