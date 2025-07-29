#include "../includes/minishell.h"

static int	skip_token(char *str,int i)
{
	char	quote_char;
	int		in_quotes;

	in_quotes = 0;
	quote_char = 0;
	while (str[i] && (str[i] != ' ' || in_quotes))
	{
		if ((str[i] == '"' || str[i] == '\'') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = str[i];
		}
		else if (str[i] == quote_char && in_quotes)
		{
			in_quotes = 0;
			quote_char = 0;
		}
		i++;
	}
	return (i);
}

static int	count_tokens(char *str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		i = skip_spaces(str,i);
		if (str[i] == '\0')
			break;
		count++;
		i = skip_token(str,i);
		if (str[i] == '\0')
			break;
	}
	return(count);
}
static char	*create_token_from_range(char *str, int start, int len)
{
	char	*token;
	int		i;

	token = malloc(len + 1);
	if (!token)
		return NULL;
	i = 0;
	while (i < len)
	{
		token[i] = str[start + i];
		i++;
	}
	token[len] = '\0';
	return (token);
}
static char	*extract_single_token(char *str, int *pos)
{
	char	*token;
	int		start;
	int		end;
	int		len;

	*pos = skip_spaces(str, *pos);
	if (str[*pos] == '\0')
		return NULL;
	start = *pos;
	*pos = skip_token(str, *pos);
	end = *pos;
	len = end - start;
	token = create_token_from_range(str, start, len);
	return (token);
}

char	**smart_split(char *str)
{
	char	**tokens;
	int		token_count;
	int		i;
	int		pos;

	if (!str)
		return NULL;
	token_count = count_tokens(str);
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if(!tokens)
		return NULL;
	i = 0;
	pos = 0;
	while (i < token_count){
		tokens[i] = extract_single_token(str, &pos);
		if (!tokens[i]){
			free_args(tokens);
			return NULL;
		}
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}