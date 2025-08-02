/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:49:27 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/29 18:27:42 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_env_var(t_expctx *ctx)
{
	char	var_name[256];
	char	*val;
	int		k;
	int		l;

	k = 0;
	l = 0;
	while (ctx->str[ctx->i] && (ft_isalnum(ctx->str[ctx->i])
			|| ctx->str[ctx->i] == '_'))
		var_name[k++] = ctx->str[ctx->i++];
	var_name[k] = '\0';
	val = get_env_value(ctx->shell->env_list, var_name);
	if (!val)
		return ;
	while (val[l])
		ctx->result[ctx->j++] = val[l++];
}

static void	handle_dollar_exp(t_expctx *ctx)
{
	if (ctx->str[ctx->i] == '?')
	{
		ctx->j = expand_exit_status(ctx->result, ctx->j, ctx->shell);
		ctx->i++;
	}
	else if (ft_isalpha(ctx->str[ctx->i]) || ctx->str[ctx->i] == '_')
		expand_env_var(ctx);
	else
	{
		ctx->result[ctx->j++] = '$';
		ctx->result[ctx->j++] = ctx->str[ctx->i++];
	}
}

static size_t	handle_env_variable(const char *str, size_t *i,
		t_minishell *shell)
{
	size_t	var_start;
	char	var_name[256];
	char	*val;

	(*i)++;
	var_start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	ft_strlcpy(var_name, str + var_start, *i - var_start + 1);
	val = get_env_value(shell->env_list, var_name);
	if (val)
		return (ft_strlen(val));
	return (0);
}

static size_t	calc_result_length(const char *str, t_minishell *shell)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			len += handle_env_variable(str, &i, shell);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*expand_variables(char *str, t_minishell *shell)
{
	t_expctx	ctx;

	if (!str)
		return (NULL);
	ctx.str = str;
	ctx.shell = shell;
	ctx.i = 0;
	ctx.j = 0;
	ctx.result = malloc(calc_result_length(str, shell) + 1);
	if (!ctx.result)
		return (NULL);
	while (ctx.str[ctx.i])
	{
		if (ctx.str[ctx.i] == '$' && ctx.str[ctx.i + 1])
		{
			ctx.i++;
			handle_dollar_exp(&ctx);
		}
		else
			ctx.result[ctx.j++] = ctx.str[ctx.i++];
	}
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}
