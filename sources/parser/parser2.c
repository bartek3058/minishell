/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:32:13 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/29 18:34:41 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char    *redirect_input_helper(char **argv)
// {
//     int i;

//     i = 0;
//     while (argv[i])
//     {
//         if (ft_strcmp(argv[i], "<") == 0)
//         {
//             if (argv[i + 1])
//                 return ft_strdup(argv[i + 1]);
//             else
//                 return NULL;
//         }
//         i++;
//     }
//     return NULL;
// }

// char    *redirect_output_helper(char **argv)
// {
//     int i;

//     i = 0;
//     while(argv[i])
//     {
//         if(ft_strcmp(argv[i], ">") == 0)
//         {
//             if(argv[i + 1] && argv[i + 1][0] != '\0')
//                 return ft_strdup(argv[i + 1]);
//             else
//                 return NULL;
//         }
//         i++;
//     }
//     return NULL;
// }

// char *redirect_double_input_helper(char **argv)
// {
// 	int	i;
//
// 	i = 0;
//	
// 	while (argv[i])
// 	{
// 		if (ft_strcmp(argv[i], "<<") == 0)
// 		{
// 			if (argv[i + 1])
// 				return ft_strdup(argv[i + 1]);
// 			else
// 				return NULL;
// 		}
// 		i++;
// 	}
// 	return NULL;
// }

// char *redirect_double_output_helper(char **argv)
// {
// 	int	i;
//
// 	i = 0;
//	
// 	while (argv[i])
// 	{
// 		if (ft_strcmp(argv[i], ">>") == 0)
// 		{
// 			if (argv[i + 1])
// 				return ft_strdup(argv[i + 1]);
// 			else
// 				return NULL;
// 		}
// 		i++;
// 	}
// 	return NULL;
// }
// char	**remove_redirections(char **argv)
// {
// 	char	**new_argv;
// 	int		i;
// 	int 	j;

// 	new_argv = malloc(sizeof(char *) * (count_args(argv) + 1));
// 	if(!new_argv)
// 		return(NULL);
// 		i = 0;
// 		j = 0;
// 		while (argv[i])
// 		{
// 			if (!ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], ">")
// 				|| !ft_strcmp(argv[i], ">>") || !ft_strcmp(argv[i], "<<"))
// 				i += 2;
// 			else
// 				new_argv[j++] = ft_strdup(argv[i++]);
// 		}
// 		new_argv[j] = NULL;
// 		return(new_argv);
// 		}
// }

int	is_operator_token(t_token *token)
{
	if (!token || !token->type)
		return (0);
	return (ft_strcmp(token->type, "|") == 0
		|| ft_strcmp(token->type, "&&") == 0
		|| ft_strcmp(token->type, "||") == 0);
}

t_token	*handle_redirection_token(t_command *cmd, t_token *token)
{
	handle_redirection(cmd, &token);
	return (token);
}

t_token	*handle_operator_token(t_command *current_cmd, t_token *token)
{
	if (ft_strcmp(token->type, "|") == 0)
		return (handle_pipe_operator(current_cmd, token));
	else if (ft_strcmp(token->type, "&&") == 0)
		return (handle_logical_and(current_cmd, token));
	else if (ft_strcmp(token->type, "||") == 0)
		return (handle_logical_or(current_cmd, token));
	return (token->next);
}

t_token	*handle_pipe_operator(t_command *current_cmd, t_token *token)
{
	current_cmd->pipe_out = 1;
	current_cmd->next = create_new_command();
	return (token->next);
}

t_token	*handle_logical_and(t_command *current_cmd, t_token *token)
{
	current_cmd->logical_op = 1;
	current_cmd->next = create_new_command();
	return (token->next);
}
