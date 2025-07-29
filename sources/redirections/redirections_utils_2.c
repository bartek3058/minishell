#include "../../includes/minishell.h"

int	open_all_input_files(t_command *cmd, int *last_fd)
{
	int	fd;
	int	i;

	i = 0;
	while (i < cmd->input_file_count)
	{
		fd = open(cmd->input_files[i], O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->input_files[i]);
			return (-1);
		}
		if (i < cmd->input_file_count - 1)
			close(fd);
		i++;
	}
	*last_fd = fd;
	return (0);
}

int	dup_last_input(int fd)
{
	if (fd >= 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("Error duplicating file descriptor");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}
int	open_all_append_files(t_command *cmd, int *last_fd)
{
	int	fd;
	int	i;

	i = 0;
	while (i < cmd->append_file_count)
	{
		fd = open(cmd->append_files[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("Error opening append file");
			return (-1);
		}
		if (i < cmd->append_file_count - 1)
			close(fd);
		i++;
	}
	*last_fd = fd;
	return (0);
}

int	dup_last_append_fd(int fd)
{
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