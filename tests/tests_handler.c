#include "minishell.h"
#include "../libft/libft.h"

void ft_test_command_handler(t_minishell *shell, int *test_nr)
{
    (void)shell;
	// Test mode selection
    int test_mode; // Change this to test different functionality
    
	test_mode = *test_nr;
    // 1: Basic command execution
    // 2: Input redirection
    // 3: Output redirection
    // 4: Append redirection
    // 5: Heredoc
    // 6: Pipe test
    // 7: Echo builtin
    // 8: Cd builtin
    // 9: Pwd builtin
    // 10: Export builtin
    // 11: Unset builtin
    // 12: Env builtin
    // 13: Exit builtin
    
    printf("\n=== RUNNING TEST MODE %d ===\n\n", test_mode);
    
    switch (test_mode)
    {
        case 1:
            ft_test_basic_command();
            break;
        case 2:
            ft_test_input_redirection();
            break;
        case 3:
            ft_test_output_redirection();
            break;
        case 4:
            ft_test_append_redirection();
            break;
        case 5:
            ft_test_heredoc();
            break;
        case 6:
            ft_test_pipe(shell);
            break;
        case 7:
            ft_test_echo();
            break;
        case 8:
            ft_test_cd();
            break;
        case 9:
            ft_test_pwd();
            break;
        case 10:
            ft_test_export(shell);
            break;
        case 11:
            ft_test_unset(shell);
            break;
        case 12:
            ft_test_env(shell);
            break;
        case 13:
            ft_test_exit(shell);
            break;
        default:
            printf("Invalid test mode\n");
    }
}

// Basic command execution test
void ft_test_basic_command(void)
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Set up command
    char *args[] = {"ls", "-la", NULL};
    cmd.args = args;
    
    printf("Testing basic command: %s %s\n", cmd.args[0], cmd.args[1]);
    
    // Execute command
    if (cmd.args && cmd.args[0])
    {
        char *path = check_path(cmd.args[0]);
        if (path)
            execute_cmd(path, cmd.args);
        else
            fprintf(stderr, "Command not found: %s\n", cmd.args[0]);
    }
}

// Input redirection test
void ft_test_input_redirection(void)
{
    t_command	cmd;
	int			stdin_copy;
	
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Create a test file
    FILE *fp = fopen("test_input.txt", "w");
    if (fp)
    {
        fprintf(fp, "This is a test file for input redirection.\n");
        fprintf(fp, "It contains multiple lines.\n");
        fclose(fp);
    }
    
    // Set up command with input redirection
    char *args[] = {"cat", NULL};
    cmd.args = args;
    cmd.input_file = "test_input.txt";
    
    printf("Testing input redirection: %s < %s\n", cmd.args[0], cmd.input_file);
    

	stdin_copy = dup(STDIN_FILENO); // Save original stdin
    // Handle input redirection
    ft_input_redirection(&cmd);
    
    // Execute command
    if (cmd.args && cmd.args[0])
    {
        char *path = check_path(cmd.args[0]);
        if (path)
            execute_cmd(path, cmd.args);
        else
            fprintf(stderr, "Command not found: %s\n", cmd.args[0]);
    }
    // Restore original stdin
    dup2(stdin_copy, STDIN_FILENO);
    close(stdin_copy);

	// Display the result
	printf("\nContent of %s:\n", cmd.input_file);
	system("cat test_input.txt");
	
	// Clean up
	printf("\nCleaning up test file...\n");
	remove("test_input.txt");
}

// Output redirection test
void ft_test_output_redirection(void)
{
    t_command cmd;
	int stdout_copy;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Set up command with output redirection
    char *args[] = {"ls", "-la", NULL};
    cmd.args = args;
    cmd.output_file = "test_output.txt";
    
    printf("Testing output redirection: %s > %s\n", cmd.args[0], cmd.output_file);
    
	stdout_copy = dup(STDOUT_FILENO); // Save original stdout
    // Handle output redirection
    ft_output_redirection(&cmd);
    
    // Execute command
    if (cmd.args && cmd.args[0])
    {
        char *path = check_path(cmd.args[0]);
        if (path)
            execute_cmd(path, cmd.args);
        else
            fprintf(stderr, "Command not found: %s\n", cmd.args[0]);
    }
	// Restore original stdout
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
    
    // Display the result
    printf("\nContent of %s:\n", cmd.output_file);
    system("cat test_output.txt");

	// Clean up
	printf("\nCleaning up test file...\n");
	remove("test_output.txt");
}

// Append redirection test
void ft_test_append_redirection(void)
{
    t_command cmd;
	int stdout_copy;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Create initial file
    FILE *fp = fopen("test_append.txt", "w");
    if (fp)
    {
        fprintf(fp, "Initial content\n");
        fclose(fp);
    }

	printf("Initial content of test_append.txt:\n");
	system("cat test_append.txt");

    // Set up command with append redirection
    char *args[] = {"echo", "Appended content", NULL};
    cmd.args = args;
    cmd.append_file = "test_append.txt";

    printf("Testing append redirection: %s %s >> %s\n", 
           cmd.args[0], cmd.args[1], cmd.append_file);
    
	
	stdout_copy = dup(STDOUT_FILENO); // Save original stdout

    // Handle append redirection (you'll need to implement this)
    // ft_append_redirection(&cmd);
	ft_output_redirection(&cmd);
    
    // Execute command
    if (cmd.args && cmd.args[0])
    {
        char *path = check_path(cmd.args[0]);
        if (path)
            execute_cmd(path, cmd.args);
        else
            fprintf(stderr, "Command not found: %s\n", cmd.args[0]);
    }
    
	// Restore original stdout
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);

    // Display the result
    printf("\nContent of %s after append:\n", cmd.append_file);
    system("cat test_append.txt");

	// Clean up
	printf("\nCleaning up test file...\n");
	remove("test_append.txt");
}

// Heredoc test
void ft_test_heredoc(void)
{
    t_command cmd;
	int stdin_copy;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Set up command with heredoc
    char *args[] = {"cat", NULL};
    cmd.args = args;
    cmd.heredoc = "EOF";
    
    printf("Testing heredoc: %s << %s\n", cmd.args[0], cmd.heredoc);
    printf("(Simulating heredoc input)\n");
    
    // Simulate heredoc content (you'll need to implement this properly)
    FILE *fp = fopen("heredoc_temp", "w");
    if (fp)
    {
        fprintf(fp, "This is line 1 of heredoc\n");
        fprintf(fp, "This is line 2 of heredoc\n");
        fprintf(fp, "EOF\n");
        fclose(fp);
    }

	stdin_copy = dup(STDIN_FILENO); // Save original stdin
    
    // Handle heredoc redirection
    ft_heredoc_redirection(&cmd);
    
    // Execute command
    if (cmd.args && cmd.args[0])
    {
        char *path = check_path(cmd.args[0]);
        if (path)
            execute_cmd(path, cmd.args);
        else
            fprintf(stderr, "Command not found: %s\n", cmd.args[0]);
    }
	// Restore original stdin
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	
	// Display the result
	printf("\nContent of heredoc_temp:\n");
	system("cat heredoc_temp");
	
	// Clean up
	printf("\nCleaning up heredoc_temp file...\n");
	remove("heredoc_temp");
}

// Pipe test
void ft_test_pipe(t_minishell *shell)
{
    t_command cmd1, cmd2;
    
    // Zero out the structs
    memset(&cmd1, 0, sizeof(t_command));
    memset(&cmd2, 0, sizeof(t_command));
    
    // Set up commands for pipe
    char *args1[] = {"ls", "-la", NULL};
    char *args2[] = {"grep", "test", NULL};
    
    cmd1.args = args1;
    cmd2.args = args2;
    
    printf("Testing pipe: %s %s | %s %s\n", 
           cmd1.args[0], cmd1.args[1], cmd2.args[0], cmd2.args[1]);
    
    // Execute pipe (you'll need to implement this)
    ft_execute_pipe(shell, &cmd1, &cmd2);
}

// Echo builtin test
void ft_test_echo(void)
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Test 1: Basic echo
    char *args1[] = {"echo", "Hello, world!", NULL};
    cmd.args = args1;
    
    printf("Testing echo builtin: %s %s\n", cmd.args[0], cmd.args[1]);
    ft_echo(cmd.args);
    
    // Test 2: Echo with -n option
    char *args2[] = {"echo", "-n", "Hello, world without newline", NULL};
    cmd.args = args2;
    
    printf("\nTesting echo with -n: %s %s %s\n", 
           cmd.args[0], cmd.args[1], cmd.args[2]);
    ft_echo(cmd.args);
    
    printf("\n"); // Add a newline for clarity after -n test
}

// Cd builtin test
void ft_test_cd(void)
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Get current directory for reference
    char cwd_before[1024];
    getcwd(cwd_before, sizeof(cwd_before));
    
    // Test 1: cd to a directory
    char *args1[] = {"cd", "..", NULL};
    cmd.args = args1;
    
    printf("Current directory: %s\n", cwd_before);
    printf("Testing cd builtin: %s %s\n", cmd.args[0], cmd.args[1]);
    ft_cd(cmd.args);
    
    // Get new directory
    char cwd_after[1024];
    getcwd(cwd_after, sizeof(cwd_after));
    printf("New directory: %s\n", cwd_after);
    
    // Test 2: cd back
    char *args2[] = {"cd", cwd_before, NULL};
    cmd.args = args2;
    
    printf("\nTesting cd back: %s %s\n", cmd.args[0], cmd.args[1]);
    ft_cd(cmd.args);
    
    // Verify we're back
    getcwd(cwd_after, sizeof(cwd_after));
    printf("Back to directory: %s\n", cwd_after);
}

// Pwd builtin test
void ft_test_pwd(void)
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Set up command
    char *args[] = {"pwd", NULL};
    cmd.args = args;
    
    printf("Testing pwd builtin: %s\n", cmd.args[0]);
    ft_pwd();
}

// Export builtin test
void ft_test_export(t_minishell *shell)	
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Test 1: Export without arguments (should display all variables)
    char *args1[] = {"export", NULL};
    cmd.args = args1;
    
    printf("Testing export builtin (list all): %s\n", cmd.args[0]);
    add_env(&(shell->env_list), cmd.args[1], cmd.args[2]);
    
    // Test 2: Export with new variable
    char *args2[] = {"export", "TEST_VAR=test_value", NULL};
    cmd.args = args2;
    
    printf("\nTesting export with variable: %s %s\n", 
           cmd.args[0], cmd.args[1]);
    add_env(&(shell->env_list), cmd.args[1], cmd.args[2]);
    
    // Verify the variable was set
    printf("\nVerifying TEST_VAR with env:\n");
    system("env | grep TEST_VAR");
}

// Unset builtin test
void ft_test_unset(t_minishell *shell)
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // First set a variable to unset
    char *args1[] = {"export", "UNSET_TEST=value_to_unset", NULL};
    cmd.args = args1;
    
    printf("Setting variable for unset test: %s %s\n", 
           cmd.args[0], cmd.args[1]);
    add_env(&(shell->env_list), cmd.args[1], cmd.args[2]);
    
    // Verify the variable was set
    printf("\nVerifying UNSET_TEST is set:\n");
    system("env | grep UNSET_TEST");
    
    // Now unset it
    char *args2[] = {"unset", "UNSET_TEST", NULL};
    cmd.args = args2;
    
    printf("\nTesting unset builtin: %s %s\n", cmd.args[0], cmd.args[1]);
    ft_unset(&(shell->env_list), cmd.args); 

    // Verify the variable was unset
    printf("\nVerifying UNSET_TEST is unset:\n");
    system("env | grep UNSET_TEST");
}

// Env builtin test
void ft_test_env(t_minishell *shell)
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Set up command
    char *args[] = {"env", NULL};
    cmd.args = args;
    
    printf("Testing env builtin: %s\n", cmd.args[0]);
    ft_env(shell->env_list);
}

// Exit builtin test
void ft_test_exit(t_minishell *shell)	
{
    t_command cmd;
    
    // Zero out the struct
    memset(&cmd, 0, sizeof(t_command));
    
    // Test with exit status
    char *args[] = {"exit", "42", NULL};
    cmd.args = args;
    
    printf("Testing exit builtin: %s %s\n", cmd.args[0], cmd.args[1]);
    printf("(This would normally exit the shell with status 42)\n");
    
    // In test mode, don't actually exit
    // Just simulate and print the status
    int status = ft_atoi(cmd.args[1]);
    printf("Exit status would be: %d\n", status);
    
    // For actual implementation, uncomment:
     ft_exit(shell);
}

void print_tokens(t_token *token)
{
    int i = 0;
    while (token)
    {
        printf("token[%d]: type='%s', value='%s'\n", i,
            token->type ? token->type : "NULL",
            token->value ? token->value : "NULL");
        token = token->next;
        i++;
    }
}