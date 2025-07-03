#include "../includes/minishell.h"

static int	expand_env_var(char *str, int *i, char *result, int j, t_minishell *shell)
{
	char	var_name[256];
	char	*var_value;
	int		k;
	int		l;

	k = 0;
	while(str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_')){
		var_name[k++] = str[*i];
		(*i)++;
	}
	var_name[k] = '\0';
	var_value = get_env_value(shell->env_list, var_name);
	if(var_value){
		l = 0;
		while(var_value[l])
			result[j++] = var_value[l++];
	}
	return j;
}

static int	expand_exit_status(char *result,int j,t_minishell *shell)
{
	char	*status_str;
	int		k;

	status_str = ft_itoa(shell->exit_status);
	if(!status_str)
		return j;
	k=0;
	while (status_str[k])
		result[j++] = status_str[k++];
	free(status_str);
	return j;
}

static int	handle_dollar_exp(char *str, int *i,char *result,int j,t_minishell *shell)
{
	if (str[*i] == '?'){
		j = expand_exit_status(result, j, shell);
		(*i)++;
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
		j = expand_env_var(str, i, result, j, shell);
	else{
		result[j++] = '$';
		result[j++] = str[*i];
		(*i)++;
	}
	return j;
}

char	*expand_variables(char *str, t_minishell *shell)
{
	char	*result;
	int		i;
	int		j;

	if(!str)
	return NULL;
	result = malloc(ft_strlen(str)*2 + 1);
	if(!result)
		return NULL;
	i = 0;
	j = 0;
	while(str[i]){
		if(str[i] == '$' && str[i+1]){
			i++;
			j = handle_dollar_exp(str, &i, result, j, shell);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return result;
}