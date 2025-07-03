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
	char	*stripped_word;
	char	quote_type;
	size_t	len;

	quote_type = 0;
	len = ft_strlen(args[*i]);
	if (len >= 2){
		if (args[*i][0] == '"' && args[*i][len - 1] == '"')
			quote_type = '"';
		else if (args[*i][0] == '\'' && args[*i][len - 1] == '\'')
			quote_type = '\'';
	}
	stripped_word = strip_quotes(args[*i]);
	if (quote_type == '\'' || !ft_strchr(stripped_word, '$')) //single quotes or not variable
		add_token(token, "WORD", stripped_word);
	else
		add_token(token, "VAR_WORD", stripped_word); // double quotes or unquoted variable
	free(stripped_word);
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
	}
}
