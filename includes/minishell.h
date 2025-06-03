#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../libft/libft.h"


// struktura reprezentujaca token z parsera

typedef struct s_token
{
	char *type; // typ tokenu (WORD, PIPE)
	char *value; // wartosc tokenu
	struct s_token *next; // wskaznik na nastepny token
}				t_token;

// struktura przechowujaca zmienne srodowiskowe
typedef struct s_env
{
	char *key; // nazwa zmiennej
	char *value; // wartosc zmiennej
	struct s_env *next; // wskaznik na nastepna zmienna
}				t_env;

// struktura reprezentujaca pojedyncze polecenie
typedef struct s_command
{
	char **args; // argumenty polecenia (args[0] to nazwa polecenia)
	char *input_file; // plik wejsciowy (< file)
	char *output_file; // plik wyjsciowy (> file)
	char *append_file; // plik do dopisania (>> file)
	char *heredoc; // heredoc delimiter (<<)
	struct s_command *next; // wskaznik na nastepne polecenie (potok)
	int pipe_fd[2]; // deskryptory potokow
}				t_command;

// glowna struktura minishell
typedef struct s_minishell
{
	t_env *env_list; // wskaznik na liste zmiennych srodowiskowych
	t_command *commands; // wskaznik na liste polecen do wykonania
	int exit_status; // status zakonczenia ostatniego polecenia
	int running; // flaga czy shell jest uruchomiony
	char *line; // aktualnie przetwarzana linia
}				t_minishell;



int		main(int argc, char **argv, char **envp);
void	minishell_loop(t_minishell *shell, char **args, t_token **token);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
int		update_existing_env(t_env *env_list, char *key, char *value);
int		add_env(t_env **env_list, char *key, char *value);
void	handle_sigint(int sig);
void	setup_signals(void);
void	init_minishell(t_minishell *shell, char **envp, t_token **token);

int		ft_strcmp(const char *s1, const char *s2);
void	minishell_loop_helper(t_minishell *shell, char **args, t_token **token);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);

//built-ins
void	ft_builtins(t_minishell *shell, char **args);
int		ft_cd(char **args);
int		ft_echo(char **args);
void	ft_exit(t_minishell *shell);
void	ft_pwd(void);
int		ft_env(t_env *env);
int		ft_unset(t_env **env_list, char *key);
char	*strip_quotes(const char *str);

//redirections
void	ft_input_redirection(t_command *cmd);
void	ft_output_redirection(t_command *cmd);
void	ft_append_redirection(t_command *cmd);
void	ft_heredoc_redirection(t_command *cmd);

//pipes
void	ft_execute_pipe(t_minishell *shell, t_command *cmd1, t_command *cmd2); // wykonuje polecenia w potoku

//utils_t
int		execute_cmd(char *path, char **args); 	// wykonuje polecenie
int		execute_command(t_minishell *shell, t_command *cmd); // sprawdza czy polecenie jest wbudowane i je wykonuje
char	*check_path(char *cmd);			// sprawdza sciezke do polecenia
int		is_builtin(char *cmd);

//utils_t_2
char	**conv_env_to_array(t_env *env); // konwersja listy zmiennych srodowiskowych na tablice
char	**tokens_to_args(t_token *token); // konwersja listy tokenow na tablice argumentow


//utils
void	init_token(t_token **token);
size_t	ft_strcpy(char *dst, const char *src);
char	*ft_strcat(char *dst, const char *src);
void	parser_helper(t_token **token, char **args, int *i);
int is_redirect_or_pipe(char *arg);

//clean-up
void	free_args(char **args);   // zwalnia pamiec po tablicy argumentow
void	free_env(t_env *env);     // zwalnia pamiec po zmiennych srodowiskowych
void	free_env_node(t_env *node); // zwalnia pamiec po pojedynczej zmiennej srodowiskowej (dla unset)
void	free_tokens(t_token *token); // zwalnia pamięc po linked liście z tokenami

//tests
void ft_test_command_handler(t_minishell *shell, int *test_nr);
void ft_test_basic_command(void);
void ft_test_input_redirection(void);
void ft_test_output_redirection(void);
void ft_test_append_redirection(void);
void ft_test_heredoc(void);
void ft_test_pipe(t_minishell *shell);
void ft_test_echo(void);
void ft_test_cd(void);
void ft_test_pwd(void);
void ft_test_export(t_minishell *shell);
void ft_test_unset(t_minishell *shell);
void ft_test_env(t_minishell *shell);
void ft_test_exit(t_minishell *shell);
void print_tokens(t_token *token); // wypisuje tokeny dla testow

//parser
void    parser(char **args, t_token **token);
void    parser_pwd(t_token **head);
char *build_echo_value(char **argv);
int count_echo_len(char **argv, int i);
void    parser_pipe(t_token **head);
void    parser_redirect_output(t_token **head, char **argv);
char    *redirect_output_helper(char **argv);
void    parser_redirect_input(t_token **head, char **argv);
char    *redirect_input_helper(char **argv);
void	parser_double_redirect_output(t_token **head, char **argv);
char 	*redirect_double_output_helper(char **argv);
void	parser_double_redirect_input(t_token **head, char **argv);
char 	*redirect_double_input_helper(char **argv);
void	parser_cd(t_token **head, char **args, int i);
void	parser_export(t_token **head, char **args);
int		is_valid_varname(const char *str);
void	add_token(t_token **head, char *key, char *value);
void	parser_unset(t_token **token, char **args);
void	parser_env(t_token **token);
void	parser_or(t_token **head);
void	parser_and(t_token **head);
void	parser_exit(t_token **head);

#endif