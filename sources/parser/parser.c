#include "../includes/minishell.h"

static void add_redirection_token(t_token **token, char **args, int *i, char *type)
{
	add_token(token, type, NULL);
	(*i)++;
	if (args[*i])
	{
		add_token(token, "WORD", args[*i]);
	}
}
static void handle_word_token(t_token **token, char **args, int *i)
{
	char	quote_type;
	size_t	len;

	quote_type = 0;
	len = ft_strlen(args[*i]);
	if (ft_strchr(args[*i], '"') || ft_strchr(args[*i], '\'')){
		if (len >= 2 && args[*i][0] == '\'' && args[*i][len - 1] == '\'')
			quote_type = '\'';
		else 
			quote_type = '"';
	}
	if (quote_type == '\'' || !ft_strchr(args[*i], '$')) //single quotes or not variable
		add_token(token, "WORD", args[*i]);
	else
		add_token(token, "VAR_WORD", args[*i]); // double quotes or unquoted variable
}

static void handle_operator_token(t_token **token, char **args, int *i)
{
	if (ft_strcmp(args[*i], "|") == 0)
		add_token(token, "|", NULL);
	else if (ft_strcmp(args[*i], "&&") == 0)
		add_token(token, "&&", NULL);
	else if (ft_strcmp(args[*i], "||") == 0)
		add_token(token, "||", NULL);
	else if (ft_strcmp(args[*i], ">") == 0)
		add_redirection_token(token, args, i, ">");
	else if (ft_strcmp(args[*i], "<") == 0)
		add_redirection_token(token, args, i, "<");
	else if (ft_strcmp(args[*i], ">>") == 0)
		add_redirection_token(token, args, i, ">>");
	else if (ft_strcmp(args[*i], "<<") == 0)
		add_redirection_token(token, args, i, "<<");
	else
		handle_word_token(token, args, i);
}

void tokenize_input(char **args, t_token **token)
{
	int i = 0;



	while (args[i])
	{
		if (is_redirect_or_pipe(args[i]))
			handle_operator_token(token, args, &i);
		else
			handle_word_token(token, args, &i);
		i++;
		//DEBUG
		// if (*token){
		// 	t_token *current = *token;
		// 	while (current->next)
		// 		current = current->next;
		// 	printf("Token created: type='%s', value='%s'\n", current->type ? current->type : "NULL", current->value ? current->value : "NULL");
		// }
		//DEBUG
	}
}
