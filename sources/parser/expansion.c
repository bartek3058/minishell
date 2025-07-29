#include "../../includes/minishell.h"

static void	expand_env_var(t_expctx *ctx)
{
	char	var_name[256];
	char	*val;
	int		k = 0;
	int		l = 0;

	while (ctx->str[ctx->i] && (ft_isalnum(ctx->str[ctx->i]) || ctx->str[ctx->i] == '_'))
		var_name[k++] = ctx->str[ctx->i++];
	var_name[k] = '\0';
	val = get_env_value(ctx->shell->env_list, var_name);
	if (!val)
		return;
	while (val[l])
		ctx->result[ctx->j++] = val[l++];
}


static int	expand_exit_status(char *res, int j, t_minishell *shell)
{
	char	*status_str;
	int		k = 0;

	status_str = ft_itoa(shell->exit_status);
	if (!status_str)
		return j;
	while (status_str[k])
		res[j++] = status_str[k++];
	free(status_str);
	return j;
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


static size_t	calc_result_length(const char *str, t_minishell *shell)
{
	size_t	len;
	size_t	i;
	size_t	var_start;
	char *val;
	char	var_name[256];

	len = 0;
	i = 0;
	while (str[i]){
		if (str[i] == '$' && str[i+1]){
			i++;
			var_start = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			ft_strlcpy(var_name, str + var_start, i - var_start + 1);
			val = get_env_value(shell->env_list, var_name);
			if(val)
				len+= ft_strlen(val);
		}
		else {
			len++;
			i++;
		}
	}
	return len;
}

char	*expand_variables(char *str, t_minishell *shell)
{
	t_expctx	ctx;

	if (!str)
		return NULL;
	ctx.str = str;
	ctx.shell = shell;
	ctx.i = 0;
	ctx.j = 0;
	ctx.result = malloc(calc_result_length(str, shell) + 1);
	if (!ctx.result)
		return NULL;
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
	return ctx.result;
}

