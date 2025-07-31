/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomek <tomek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:31:08 by brogalsk          #+#    #+#             */
/*   Updated: 2025/07/31 23:05:43 by tomek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

// struktura reprezentujaca token z parsera
typedef struct s_token
{
	char			*type; // typ tokenu (WORD, PIPE)
	char			*value; // wartosc tokenu
	struct s_token	*next; // wskaznik na nastepny token
}	t_token;

// struktura przechowujaca zmienne srodowiskowe
typedef struct s_env
{
	char			*key; // nazwa zmiennej
	char			*value; // wartosc zmiennej
	struct s_env	*next; // wskaznik na nastepna zmienna
}	t_env;

// struktura reprezentujaca pojedyncze polecenie
typedef struct s_command
{
	char				**args; // argumenty polecenia
						// (args[0] to nazwa polecenia)
	char				**input_files; // plik wejsciowy (< file), 
						// tablica plików wejściowych dla wielu redirekcji
	char				**output_files; // plik wyjsciowy (> file), 
						// tablica plików wyjściowych dla wielu redirekcji
	char				**append_files; // plik do dopisania (>> file), 
						// tablica plików wyjściowych dla wielu redirekcji
	char				*heredoc; // heredoc delimiter (<<)
	int					logical_op; // operator logiczny (&&, ||)
	int					pipe_out; // czy polecenie ma byc wyslane 
						// do potoku (1 jeśli tak, 0 jeśli nie)
	struct s_command	*next; // wskaznik na nastepne polecenie (potok)
	int					pipe_fd[2]; // deskryptory potokow
	int					input_file_count; // jeśli chcemy 
								// obsłużyć wiele redirekcji
	int					output_file_count; // jeśli chcemy 
								// obsłużyć wiele redirekcji
	int					append_file_count; // jeśli chcemy 
								// obsłużyć wiele redirekcji
	pid_t				pid; // PID procesu wykonujacego polecenie
}	t_command;

// glowna struktura minishell
typedef struct s_minishell
{
	t_env			*env_list; // wskaznik na liste zmiennych srodowiskowych
	t_command		*commands; // wskaznik na liste polecen do wykonania
	int				exit_status; // status zakonczenia ostatniego polecenia
	int				running; // flaga czy shell jest uruchomiony
	char			*line; // aktualnie przetwarzana linia
}	t_minishell;

//pomocnicza struktura w expansion.c obchodzimy warunek norminette max 5 argum
typedef struct s_expctx
{
	char			*str;
	char			*result;
	int				i;
	int				j;
	t_minishell		*shell;
}	t_expctx;


int			main(int argc, char **argv, char **envp);
void		minishell_loop(t_minishell *shell, char **args, t_token **token);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
int			update_existing_env(t_env *env_list, char *key, char *value);
int			add_env(t_env **env_list, char *key, char *value);
void		handle_sigint(int sig);
void		setup_signals(void);
void		init_minishell(t_minishell *shell, char **envp, t_token **token);

int			ft_strcmp(const char *s1, const char *s2);
void		minishell_loop_helper(t_minishell *shell, char **args,
				t_token **token);
char		**ft_split(char const *s, char c);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);

//built-ins
int			ft_cd(char **args);
int			ft_echo(char **args);
void	ft_exit(t_minishell *shell, char **args, t_command *cmd, t_token **token, char **argv);
void		ft_pwd(void);
int			ft_env(t_env *env);
int			ft_unset(t_env **env_list, char **args);
int			ft_export(t_minishell *shell, char **args);
char		*strip_quotes(const char *str);
void		remove_env_node(t_env **env_list, char *key);
int			handle_export_with_value(t_minishell *shell, char *arg);
int	handle_export_without_value(t_minishell *shell, char *arg);
int	export_with_equal(t_minishell *shell, char *arg);
int	export_without_equal(t_minishell *shell, char *arg);
void	ft_builtins_part1(t_minishell *shell, char **args, t_command *cmd, t_token **token, char **argv);
void	ft_builtins_part2(t_minishell *shell, char **args);
void	ft_builtins(t_minishell *shell, char **args, t_command *cmd, t_token **token, char **argv);

//redirections
int			ft_input_redirection(t_command *cmd);
int			ft_output_redirection(t_command *cmd);
int			ft_append_redirection(t_command *cmd);
void		ft_heredoc_redirection(t_command *cmd);
int	open_and_truncate_outputs(t_command *cmd, int *last_fd);
int	dup_last_output(int fd);
void	write_heredoc_to_tmp(char *delimiter);
void	redirect_heredoc_input(void);
int	dup_last_input(int fd);
int	open_all_input_files(t_command *cmd, int *last_fd);
int	open_all_append_files(t_command *cmd, int *last_fd);
int	dup_last_append_fd(int fd);

//pipes
void	ft_execute_pipe(t_minishell *shell, t_command *cmd1, t_command *cmd2, t_token **token, char **args);
void	ft_execute_multiple_pipes(t_minishell *shell, t_command *start_cmd, t_token **token, char **args);
void	ft_pipe_child(int pipefd[2], int is_first_cmd,
		t_command *cmd, char **envp, t_token **token, char **args);
void close_all_pipes(int **pipes, int pipe_count);
void	ft_close_pipes(int *pipefd);
int count_pipe_commands(t_command *start_cmd);
int	**create_pipes(int pipe_count);
void		free_pipes(int **pipes, int pipe_count);
void setup_pipe_redirections(int **pipes, int cmd_index, int pipe_count);
void	execute_child_command(t_command *cmd, t_minishell *shell, t_token **token, char **args);
pid_t	*fork_all_processes(t_command *start_cmd, int **pipes,
		int pipe_count, t_minishell *shell, t_token **token, char **args);
void		wait_for_children(pid_t *pids, int pipe_count, t_minishell *shell);
void	ft_pipe_redirection(int *pipefd, int is_first_cmd);
//exec
int	execute_command_chain(t_minishell *shell, t_command *cmd_list, t_token **token, char **args);
int			setup_redirections(t_command *cmd);

//utils_t
int			execute_cmd(char *path, char **args, t_env *env_list);
					// wykonuje polecenie
int	execute_command(t_minishell *shell, t_command *cmd, t_token **token, char **args);
					// sprawdza czy polecenie jest wbudowane i je wykonuje
char		*check_path(char *cmd);			// sprawdza sciezke do polecenia
int			is_builtin(char *cmd);
int			return_error(char *origin, char *identifier, char *message);

//utils_t_2
char		**conv_env_to_array(t_env *env);
			// konwersja listy zmiennych srodowiskowych na tablice
char		**tokens_to_args(t_token *token);
			// konwersja listy tokenow na tablice argumentow
char		*get_env_value(t_env *env_list, char *key);

//utils_validations
int			is_valid_var_or_assign(const char *str);
int			is_valid_varname(const char *str);
int			is_numeric_string(const char *str);
int			validate_numeric_arg(const char *str);

//utils
void		init_token(t_token **token);
size_t		ft_strcpy(char *dst, const char *src);
char		*ft_strcat(char *dst, const char *src);
void		parser_helper(t_token **token, char **args, int *i);
int			is_redirect_or_pipe(char *arg);
void		print_tokens(t_token *token);
			// wypisuje liste tokenow do konsoli (debugging)
int			count_args(char **args);
int	exec_builtin_command(t_minishell *shell, t_command *cmd, t_token **token, char **args);
int	execute_single_command(t_minishell *shell, t_command *cmd, t_token **token, char **args);
int	execute_pipe_sequence(t_minishell *shell, t_command *start_cmd, t_token **token, char **args);
int	count_pipe_commands_2(t_command *start_cmd);
t_command *skip_pipe_sequence(t_command *current);
t_command *handle_logical_operators(t_command *current, int exit_status);
t_command *handle_or_operator(t_command *current, int exit_status);
t_command *handle_and_operator(t_command *current, int exit_status);
int	handle_env_entry(t_env *current, char **arr, int i);
int	fill_env_array(t_env *env, char **arr);
int	count_tokens_2(t_token *token);
void	fill_args_array(char **args, t_token *token);

//clean-up
void		free_args(char **args);// zwalnia pamiec po tablicy argumentow
void		free_env(t_env *env);// zwalnia pamiec po zmiennych srodowiskowych
void		free_env_node(t_env *node); // zwalnia pamiec po pojedynczej 
					// zmiennej srodowiskowej (dla unset)
void		free_tokens(t_token *token);
				// zwalnia pamięc po linked liście z tokenami
void		cleanup_and_return(char **args, char *line, t_token *token);
				// zwalnia pamiec po args, linii i tokenach
void	free_command(t_command *cmd);
void	free_str_array(char **arr);
void	free_command_list_2(t_command *cmd_list);
void	free_input_files(t_command *cmd_list);
void	free_output_files(t_command *cmd_list);
void	free_append_files(t_command *cmd_list);




//parser
t_command	*parse_command_chain(t_token *tokens, t_minishell *shell);
// char		*redirect_output_helper(char **argv);
// char		*redirect_input_helper(char **argv);
// char		*redirect_double_output_helper(char **argv);
// char		*redirect_double_input_helper(char **argv);
void		add_token(t_token **head, char *key, char *value);
void		tokenize_input(char **args, t_token **token);
int			skip_spaces(char *str,int i);
void	handle_redirect_token(t_token **token, char **args, int *i, int redirect_len);
void	handle_operator_token_2(t_token **token, char **args, int *i);
void	add_redirection_token(t_token **token, char **args, int *i, char *type);
int	is_command_token(t_token *token);
int	is_redirection_token(t_token *token);
int	is_operator_token(t_token *token);
t_token	*handle_redirection_token(t_command *cmd, t_token *token);
t_token	*handle_operator_token(t_command *current_cmd, t_token *token);
t_token	*handle_pipe_operator(t_command *current_cmd, t_token *token);
t_token	*handle_logical_and(t_command *current_cmd, t_token *token);
t_token	*handle_logical_or(t_command *current_cmd, t_token *token);
void	handle_redirection(t_command *cmd, t_token **token);
void	handle_heredoc_redirection(t_command *cmd, t_token **token);
void	handle_append_redirection(t_command *cmd, t_token **token);
void	handle_output_redirection(t_command *cmd, t_token **token);
void	handle_input_redirection(t_command *cmd, t_token **token);
void init_command_node(t_command **cmd_list, t_command **current_cmd, t_command **last_cmd);
t_command	*parse_command_chain(t_token *tokens, t_minishell *shell);
void	handle_pipe_token(t_command **current_cmd, t_command **last_cmd, t_token **token);
void	handle_operator_and_reset(t_command **current_cmd, t_command **last_cmd, t_token **token);
void child_process_exec(char *path, char **args, char **envp);
char *search_in_paths(char **paths, char *cmd);
void	execute_child_process(t_minishell *shell, t_command *cmd, t_token **token, char **args);
// expansion
char		*expand_variables(char *str, t_minishell *shell);


//smart split
char		**smart_split(char *str);

// Function prototypes to add
t_command	*create_new_command(void);
void		free_command_list(t_command *cmd_list);

#endif
