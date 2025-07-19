#include "../includes/minishell.h"

static void add_redirection_token(t_token **token, char **args, int *i, char *type)
{
	char	*arg;
	char	*filename;
	int		type_len;

	arg = args[*i];
	type_len = (int)ft_strlen(type);

	//check if redir and filename are combilned (no space)
	if ((int)ft_strlen(arg) > type_len && 
		ft_strncmp(arg, type, type_len) == 0)
	{
		//split redirtoken and filename
		add_token(token, type, NULL);
		filename = arg + type_len; //skip past operator
		if (*filename != '\0')
			add_token(token, "WORD", filename);
	}
	else
	{
		//Normal case (space after redir token)
		add_token(token, type, NULL);
		(*i)++;
		if (args[*i])
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

static int	starts_with_redirect(char *arg)
{
	if (!arg)
		return(0);
	if (ft_strncmp(arg, ">>", 2) == 0 || ft_strncmp(arg, "<<", 2) == 0)
		return (2); //double redirect
	if (arg[0] == '>' || arg[0] == '<')
		return (1); //single redirect
	return(0);
}

static void handle_operator_token(t_token **token, char **args, int *i)
{
	int	redirect_len;
	
	redirect_len = starts_with_redirect(args[*i]);
	if (redirect_len > 0){
		if (redirect_len == 2){
			if (args[*i][0] == '>')
				add_redirection_token(token, args, i, ">>");
			else
				add_redirection_token(token, args, i, "<<");
		}
		else{
			if (args[*i][0] == '>')
				add_redirection_token(token, args, i, ">");
			else
				add_redirection_token(token, args, i, "<");
		}
		return;
	}
	else if (ft_strcmp(args[*i], "|") == 0)
		add_token(token, "|", NULL);
	else if (ft_strcmp(args[*i], "&&") == 0)
		add_token(token, "&&", NULL);
	else if (ft_strcmp(args[*i], "||") == 0)
		add_token(token, "||", NULL);
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
