#include "minishell.h"

static void	child_redirect(t_cmd *current, int prev_fd, int pipe_fds[2])
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)  //dite si napoji stdin na prev_fd
		// stdin ted ukazuje na pref_fd a dite do nej muze zapsat
			exit(1); //chyba v presmerovani
		close(prev_fd);  //stdin uz ukazuje na pref_fd, take pref_fd muzeme zavrit
	}
	if (current->next)
	{
		close(pipe_fds[0]); //zavre se, u tam netecou zadna data
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)  //napoji se fds[i]
			exit (1);
		close(pipe_fds[1]);	// uz tento fd protoze se uz na nej napojil
	}
}

void	child_process(int prev_fd, int pipe_fds[2], t_cmd *current,	t_shell *shell)
{
	int exit_status;

	child_signal_setup();	
	child_redirect(current, prev_fd, pipe_fds);  // nedavam pipe_fds[2] je to ptr
	//dite si pripravolo cteci vstup pro data, ktery pouzije a vypisovaci vystup
	//  pro data,ktera vytvori
	if (current->redir)
	{
		if (execute_redir(current->redir))  // == 1 error
		{
			free_shell(&shell);
			exit(1);
		}
	}
	if	(!current->tokens || !current->tokens[0])
	//pokud red redid neni prikaz, pouze se vytvori soubor ( >soubor.txt)
	{
		free_shell(&shell);
		exit (0);
	}
	if (current->builtin != NONE)  //je builtin
	{
		exit_status = execute_builtin_cmd(current, shell);  // pouze pokud pipa  
		// do ktere jde vstup do roury
		free_shell(&shell); //konec procesu, nutne uvolnit
		exit(exit_status);
	}
	execute_binary_cmd(current, shell);
	exit (0);
}
