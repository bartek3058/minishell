#include "../../includes/minishell.h"

int	open_and_truncate_outputs(t_command *cmd, int *last_fd)
{
	int	fd;
	int	i;

	i = 0;
	while (i < cmd->output_file_count)
	{
		fd = open(cmd->output_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(cmd->output_files[i]);
			return (-1);
		}
		if (i < cmd->output_file_count - 1)
			close(fd);
		i++;
	}
	*last_fd = fd;
	return (0);
}

int	dup_last_output(int fd)
{
	if (fd >= 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("Error duplicating file descriptor");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}
void	write_heredoc_to_tmp(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("heredoc: open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

void	redirect_heredoc_input(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc: open for read");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("heredoc: dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	unlink(".heredoc_tmp");
}