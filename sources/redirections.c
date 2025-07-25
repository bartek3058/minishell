#include "../includes/minishell.h"

int	ft_output_redirection(t_command *cmd)
{
	int	fd;
	int	i;

	if (!cmd->output_files || cmd->output_file_count == 0)
		return (0);
	i = 0;
	while (i < cmd->output_file_count)
	{
		fd = open(cmd->output_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(cmd->output_files[i]);
			return(-1);
		}
		if (i < cmd->output_file_count - 1)
			close(fd);
		i++;
	}
	if (fd >= 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("Error duplicating file descriptor");
			close(fd);
			return(-1);
		}
		close(fd);
	}
	return (0);
}

void	ft_heredoc_redirection(t_command *cmd)
{
	int fd;
	char *line;
	char *delimiter;

	if (!cmd->heredoc)
		return;
	delimiter = cmd->heredoc;

	// Open a temporary file for heredoc content
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

	// Reopen for reading and redirect STDIN
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc: open for read");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("heredoc: dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
	unlink(".heredoc_tmp");
}

int ft_input_redirection(t_command *cmd)
{
	int	fd;
	int	i;

	fd = -1;
	i = 0;
	//DEBUG
	// printf("Input files:\n");
	// for (int i = 0; i < cmd->input_file_count; i++)
	// 	printf("  [%d]: %s\n", i, cmd->input_files[i]);
	//END DEBUG
	if (!cmd->input_files || cmd->input_file_count == 0)
		return 0;
	while (i < cmd->input_file_count)
	{

		//DEBUG
		// printf("Opening file %s\n", cmd->input_files[i]);
		//END DEBUG
		fd = open(cmd->input_files[i], O_RDONLY);
		//DEBUG
		// printf("Opened file %s\n", cmd->input_files[i]);
		//END DEBUG
		if (fd < 0)
		{
			perror(cmd->input_files[i]);
			//printf("Error opening %s, exiting with 1\n", cmd->input_files[i]);
			return(-1);
		}
		if (i < cmd->input_file_count - 1)
			close(fd);
		i++;
	}
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("Error duplicating file descriptor");
			close(fd);
			return(-1);
		}
		close(fd);
	}
	return 0;
}

int ft_append_redirection(t_command *cmd)
{
	int	fd;
	int	i;

	if (!cmd->append_files || cmd->append_file_count == 0)
		return (0);
	i = 0;
	while (i < cmd->append_file_count)
	{
		fd = open(cmd->append_files[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("Error opening append file");
			return (-1);
		}
		if (i < cmd->append_file_count - 1)
			close(fd);
		i++;
	}
	if (fd >= 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("Error duplicating file descriptor");
			close(fd);
			exit(1);
		}
		close(fd);
	}
	return (0);
}