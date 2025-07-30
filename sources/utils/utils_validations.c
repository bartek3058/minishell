/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:31:29 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/30 10:35:08 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_var_or_assign(const char *str)
{
	char	*eq;
	int		i;

	if (!str)
		return (0);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		if (eq == str)
			return (0);
		i = 0;
		while (&str[i] < eq)
		{
			if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
				return (0);
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (is_valid_varname(str));
}

int	is_valid_varname(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_numeric_string(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_numeric_arg(const char *str)
{
	char	*stripped;
	int		valid;

	stripped = strip_quotes(str);
	if (!stripped)
		return (0);
	valid = is_numeric_string(stripped);
	free(stripped);
	return (valid);
}
