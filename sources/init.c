#include "../includes/minishell.h"

int	update_existing_env(t_env *env_list, char *key, char *value)
{
	t_env *current;

	current = env_list;
	while (current)
	{
		// jesli klucz juz istnieje aktualizujemy wartosc
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value); //zwalniamy stara wartosc
			current->value = ft_strdup(value); // ustawiamy nowa
			return(1); // znaleziono i zaaktualizowano
		}
		current = current->next;
	}
	return (0); // nie znaleziono
}

int add_env(t_env **env_list, char *key, char *value)
{
	t_env *new_env;
	t_env *current;

	// sprawdzam czy zmienna juz istnieje jesli tak aktualizuje ja
	if (*env_list && update_existing_env(*env_list, key, value))
		return (0);
	// tworzymy i alokujemy pamiec na nowy element
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	// kopiujemy klucz i jego wartosc
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = new_env;
		return (0);
	}
	// dodajemy nowy element na koniec listy
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_env;
	return (0);
}


void handle_sigint(int sig)
{
	(void)sig; // wyswietl nowa linie i prompt
	//resetowanie readline dla nowego prompta - to gotowe funkcje z tabelki
	write(1, "\n", 1);
	rl_on_new_line(); // informuje, ze kursor znajduje sie na nowej linii
	rl_replace_line("", 0); // zastepuje aktualna linie pustym ciagiem znakow
	rl_redisplay(); //wymusza odswiezenie wyswietlanego tekstu
	//exit_code = 130; lub inna zmienna, która bedzie ustawiana
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint); // ustawienie obslugi Ctrl+c (SIGINT)
	signal(SIGQUIT, SIG_IGN); // ignorowanie Ctrl+\ (SIGQUIT)
}

void	init_minishell(t_minishell *shell, char **envp, t_token **token)
{
	int i;
	char *key;
	char *value;
	char *eq_pos;
	shell->env_list = NULL; // inicjalizacja podstawowych pol struktury
	shell->commands = NULL;
	shell->exit_status = 0;
	shell->running = 1;
	shell->line = NULL;
	*token = NULL; // inicjalizacja listy tokenow
	i = 0; // inicjalizacja listy zmiennych srodowiskowych
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			key = ft_substr(envp[i], 0, eq_pos - envp[i]); // wydziel klucz (czesc przed '=')
			value = ft_strdup(eq_pos + 1); // wydziel wartosc (czesc po '=')
			add_env(&(shell->env_list), key, value); // dodaj zmienna do listy
			free(key);
			free(value);
		}
		i++;
	}
	setup_signals();
}
