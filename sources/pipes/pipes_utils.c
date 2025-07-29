#include "../../includes/minishell.h"

void close_all_pipes(int **pipes, int pipe_count)
{
	int	i;
	
	i = 0;
	while (i < pipe_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
void	ft_close_pipes(int *pipefd)
{
    close(pipefd[0]);
    close(pipefd[1]);
}


int count_pipe_commands(t_command *start_cmd)
{
	t_command	*current;
	int			count;

	current = start_cmd;
	count = 0;
	while (current && current->pipe_out)
	{
		count++;
		current = current->next;
	}
	count++; // Add final command
	return (count);
}

int	**create_pipes(int pipe_count)
{
	int		**pipes;
	int		i;

	pipes = malloc(sizeof(int *) * pipe_count - 1);
	if (!pipes)
		return(0);
	i = 0;
	while (i < pipe_count - 1){
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0){
			perror("pipe");
			return(0);
		}
		i++;
	}
	return(pipes);
}

void		free_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count - 1){
		free(pipes[i]);
		i++;
	}
	free(pipes);
}