#define _XOPEN_SOURCE 700  // for VSCODE not to underline the structures
#include "minishell.h"

int	g_status = 0;

/**
 * @internal
 * @brief Handler for SIGINT (Ctrl+C) in interactive mode.
 * * Moves to a new line, clears the current Readline buffer, and 
 * redisplays the prompt. Updates the global status to 130.
 * * @param sig The signal number (SIGINT).
 */
static void	handle_sigint(int sig)
{
	(void)sig;
	g_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Configures signal handling for the main shell interactive mode.
 * * Sets SIGINT (Ctrl+C) to display a new prompt and SIGQUIT (Ctrl+\) 
 * to be ignored. This ensures the shell remains responsive and 
 * clean during user input.
 */
void	signal_setup(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Resets signal behavior to default for child processes.
 * * Used after fork() to ensure that the command being executed 
 * can be interrupted or terminated normally by SIGINT and SIGQUIT.
 */
void	child_signal_setup(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Sets the parent shell to ignore signals while a child is running.
 * * Prevents the main shell from reacting to Ctrl+C or Ctrl+\ while 
 * it is waiting for a foreground command to finish.
 */
void	parent_signal_setup(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
