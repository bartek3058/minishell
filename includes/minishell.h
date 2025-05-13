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

// struktura reprezentujaca token z parsera

typedef struct s_token
{
	int type; // typ tokenu (WORD, PIPE)
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
void	minishell_loop(t_minishell *shell, char **args);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
int		update_existing_env(t_env *env_list, char *key, char *value);
int		add_env(t_env **env_list, char *key, char *value);
void	handle_sigint(int sig);
void	setup_signals(void);
void	init_minishell(t_minishell *shell, char **envp);

int		ft_strcmp(const char *s1, const char *s2);
void	minishell_loop_helper(t_minishell *shell, char **args);
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


//utils_t
void	execute_cmd(char *path, char **args); 	// wykonuje polecenie
char	*check_path(char *cmd);			// sprawdza sciezke do polecenia
char	**conv_env_to_array(t_env *env); // konwersja listy zmiennych srodowiskowych na tablice
char	**tokens_to_args(t_token *token); // konwersja listy tokenow na tablice argumentow

//clean-up
void	free_args(char **args);   // zwalnia pamiec po tablicy argumentow
void	free_env(t_env *env);     // zwalnia pamiec po zmiennych srodowiskowych
void	free_env_node(t_env *node); // zwalnia pamiec po pojedynczej zmiennej srodowiskowej (dla unset)

#endif