#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

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



int main(void);
void	minishell_loop(char *input);
void	ft_exit(void);
void	ft_builtins(char *input);
void	ft_pwd(void);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif