#include "../includes/minishell.h"

char    *redirect_input_helper(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        if (ft_strcmp(argv[i], "<") == 0)
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

void    parser_redirect_input(t_token **head, char **argv)
{
    t_token *new_token;
    t_token *temp;
    char    *filename;

    filename = redirect_input_helper(argv);
    if(!filename)
        printf("Wrong filename !\n");
    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return ;
    new_token->type = ft_strdup("redirect_input");
    new_token->value = filename;
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

char    *redirect_output_helper(char **argv)
{
    int i;

    i = 0;
    while(argv[i])
    {
        if(ft_strcmp(argv[i], ">") == 0)
        {
            if(argv[i + 1] && argv[i + 1][0] != '\0')
                return ft_strdup(argv[i + 1]);
            else
                return NULL;
        }
        i++;
    }
    return NULL;
}

void    parser_redirect_output(t_token **head, char **argv)
{
    t_token *new_token;
    t_token *temp;
    char    *filename;
    
    filename = redirect_output_helper(argv);
    if(!filename)
        printf("Wrong filename !\n");
    new_token = malloc(sizeof(t_token));
    if(!new_token)
        return ;
    new_token->type = ft_strdup("redirect_output");
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

void    parser_pipe(t_token **head)
{
    t_token *new_token;
    t_token *temp;

    new_token = malloc(sizeof(t_token));
    if(!new_token)
        return ;
    temp = *head;
    new_token->type = ft_strdup("pipe");
    new_token->value = NULL;
    new_token->next = NULL;
    if(*head == NULL)
        *head = new_token;
    else
    {
        while(temp->next)
            temp = temp->next;
        temp->next = new_token;
    }
}