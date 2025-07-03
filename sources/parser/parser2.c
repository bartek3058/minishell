#include "../includes/minishell.h"

char    *redirect_input_helper(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        if (ft_strcmp(argv[i], "<") == 0)
        {
            if (argv[i + 1])
                return ft_strdup(argv[i + 1]);
            else
                return NULL;
        }
        i++;
    }
    return NULL;
}

char    *redirect_output_helper(char **argv)
{
    int i;

    i = 0;
    while(argv[i])
    {
        if(ft_strcmp(argv[i], ">") == 0)
        {
            if(argv[i + 1] && argv[i + 1][0] != '\0')
                return ft_strdup(argv[i + 1]);
            else
                return NULL;
        }
        i++;
    }
    return NULL;
}

char *redirect_double_input_helper(char **argv)
{
	int	i;

	i = 0;
	
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<<") == 0)
		{
			if (argv[i + 1])
				return ft_strdup(argv[i + 1]);
			else
				return NULL;
		}
		i++;
	}
	return NULL;
}

char *redirect_double_output_helper(char **argv)
{
	int	i;

	i = 0;
	
	while (argv[i])
	{
		if (ft_strcmp(argv[i], ">>") == 0)
		{
			if (argv[i + 1])
				return ft_strdup(argv[i + 1]);
			else
				return NULL;
		}
		i++;
	}
	return NULL;
}
