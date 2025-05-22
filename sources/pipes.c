#include "../includes/minishell.h"

static void	ft_pipe_redirection(int *pipefd, int is_first_cmd)
{
    if (is_first_cmd)
    {
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]); // Close write end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
    }
}

static void	ft_close_pipes(int *pipefd)
{
    close(pipefd[0]);
    close(pipefd[1]);
}

static void	ft_pipe_child(int pipefd[2], int is_first_cmd, t_command *cmd, char **envp)
{
    ft_pipe_redirection(pipefd, is_first_cmd);
    char *path = check_path(cmd->args[0]);
    if (path)
        execve(path, cmd->args, envp);
    perror("execve");
    exit(EXIT_FAILURE);
}

void	ft_execute_pipe(t_minishell *shell, t_command *cmd1, t_command *cmd2)
{
    int pipefd[2];
    pid_t pid1, pid2;
    char **envp = conv_env_to_array(shell->env_list);

    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        return;
    }
    pid1 = fork();
    if (pid1 == 0)
        ft_pipe_child(pipefd, 1, cmd1, envp);
    pid2 = fork();
    if (pid2 == 0)
        ft_pipe_child(pipefd, 0, cmd2, envp);
    ft_close_pipes(pipefd);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    free_args(envp);
}