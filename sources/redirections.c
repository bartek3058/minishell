#include "../includes/minishell.h"

void	ft_input_redirection(t_command *cmd)
{
	int fd;

	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening input file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("Error duplicating file descriptor");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	ft_output_redirection(t_command *cmd)
{
	int fd;

	if (cmd->output_file || cmd->append_file)
	{
		if (cmd->append_file)
			fd = open(cmd->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("Error duplicating file descriptor");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

// Append redirection handler (do wyrzucenia bo oba ogarnięte w output)
void ft_append_redirection(t_command *cmd)
{
    if (!cmd->append_file)
        return;
        
    int fd = open(cmd->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    
    // Save original stdout
    //int stdout_copy = dup(STDOUT_FILENO);
    
    // Redirect stdout to the file
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return;
    }
    
    close(fd);
    
    // Note: After command execution, you'll need to restore stdout:
    // dup2(stdout_copy, STDOUT_FILENO);
    // close(stdout_copy);
}

void	ft_heredoc_redirection(t_command *cmd)
{
    int		fd;
    char	*line;
    char	*delimiter;

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