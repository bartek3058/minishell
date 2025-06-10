#include "../includes/minishell.h"

void    parser(char **args, t_token **token)
{
    int i;
    i = 0;
    while(args[i] != NULL)
    {
        if (ft_strcmp(args[i], "pwd") == 0)
            parser_single(token, args, &i);
        else if (ft_strcmp(args[i], "echo") == 0)
            parser_multi(token, args, &i);
        else if (ft_strcmp(args[i], "export") == 0)
		    parser_multi(token, args, &i);
	    else if (ft_strcmp(args[i], "unset") == 0)
		    parser_multi(token, args, &i);
	    else if (ft_strcmp(args[i], "env") == 0)
		    parser_single(token, args, &i);
        else if (ft_strcmp(args[i], "cd") == 0)
            parser_multi(token, args, &i);
		else if (ft_strcmp(args[i], "exit") == 0)
			parser_single(token, args, &i);
        else if (is_redirect_or_pipe(args[i]))
            parser_helper(token, args, &i);
		else
			parser_multi(token, args, &i); // external commands
        i++;
    }
}
