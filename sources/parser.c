#include "../includes/minishell.h"

void	parser_pipe(t_token **head, char **argv)
{
	t_token *new_token;
	t_token *temp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	temp = *head;
	new_token->type = "pipe";
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
	free(temp);
}
}

void	echo_init(int *i, char **argv)
{

	if(argv[i + 1] == "-n")
	{
		new_token->type = "echo_n";
		new_token->value = echo_helper(argv, &len, &pos, &i);
		new_token->next = NULL;
		i = 1;
	}
	else
	{
		new_token->type = "echo";
		new_token->value = echo_helper(argv, &len, &pos, &i);
		new_token->next = NULL;
		i = 0;
	}
	
}

char	*echo_helper(char **argv, int *len, int *pos, int *i)
{
	int	i;
	char *result;

	
	while(argv[i] && ft_strcmp(argv[i], "|" != 0))
		len += ft_strlen(argv[i++]) + 1;
	if (len == 0)
		return (ft_strdup(""));
	result = malloc(len);
	if(!result)
		return NULL;
	i = 1;
	while (argv[i] && ft_strcmp(argv[i], "|"))
	{
		ft_strcpy(result + pos, argv[i]);
		pos += ft_strlen(argv[i]);
		if(argv[i + 1] && ft_strcmp(argv[i + 1], "|") != 0)
			result[pos++];
		i++;
	}
	result[pos] = '\0';
	return result;
}

void	parser_echo(t_token **head, char **argv)
{
	t_token *new_token;
	t_token *temp;
	int i;
	int	len;
	int pos;
	
	len = 0;
	pos = 0;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	temp = *head;
	echo_init(&i, argv, &pos, &len);
	if(*head == NULL)
		*head = new_token;
	else
	{
		while(temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	free(temp);
}
}

void	parser_pwd(t_token **head)
{
	t_token *new_token = malloc(sizeof(t_token));
	t_token *temp;
	if (!new_token)
		return ;
	temp = *head;
	new_token->type = "pwd";
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
	free(temp);
}