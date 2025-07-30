/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:39:26 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/29 18:43:05 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_redirection_token(t_token **token, char **args, int *i, char *type)
{
	char	*arg;
	char	*filename;
	int		type_len;

	arg = args[*i];
	type_len = (int)ft_strlen(type);
	if ((int)ft_strlen(arg) > type_len
		&& ft_strncmp(arg, type, type_len) == 0)
	{
		add_token(token, type, NULL);
		filename = arg + type_len;
		if (*filename != '\0')
			add_token(token, "WORD", filename);
	}
	else
	{
		add_token(token, type, NULL);
		if (args[*i + 1])
		{
			add_token(token, "WORD", args[*i + 1]);
			(*i)++;
			(*i)++;
		}
	}
}

static void	handle_word_token(t_token **token, char **args, int *i)
{
	char	quote_type;
	size_t	len;

	quote_type = 0;
	len = ft_strlen(args[*i]);
	if (ft_strchr(args[*i], '"') || ft_strchr(args[*i], '\''))
	{
		if (len >= 2 && args[*i][0] == '\'' && args[*i][len - 1] == '\'')
			quote_type = '\'';
		else
			quote_type = '"';
	}
	if (quote_type == '\'' || !ft_strchr(args[*i], '$'))
		add_token(token, "WORD", args[*i]);
	else
		add_token(token, "VAR_WORD", args[*i]);
}

static int	starts_with_redirect(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strncmp(arg, ">>", 2) == 0 || ft_strncmp(arg, "<<", 2) == 0)
		return (2);
	if (arg[0] == '>' || arg[0] == '<')
		return (1);
	return (0);
}

void	handle_operator_token_2(t_token **token, char **args, int *i)
{
	int	redirect_len;

	redirect_len = starts_with_redirect(args[*i]);
	if (redirect_len > 0)
	{
		handle_redirect_token(token, args, i, redirect_len);
		return ;
	}
	if (ft_strcmp(args[*i], "|") == 0)
		add_token(token, "|", NULL);
	else if (ft_strcmp(args[*i], "&&") == 0)
		add_token(token, "&&", NULL);
	else if (ft_strcmp(args[*i], "||") == 0)
		add_token(token, "||", NULL);
	else
		handle_word_token(token, args, i);
}

void	tokenize_input(char **args, t_token **token)
{
	int	i;
	int	old_i;

	i = 0;
	while (args[i])
	{
		old_i = i;
		if (is_redirect_or_pipe(args[i]))
		{
			handle_operator_token_2(token, args, &i);
		}
		else
		{
			handle_word_token(token, args, &i);
		}
		if (i == old_i)
			i++;
	}
}
