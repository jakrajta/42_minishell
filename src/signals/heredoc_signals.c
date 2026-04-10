#define _XOPEN_SOURCE 700  // ERASE 
#include "minishell.h"

/**
 * @brief Signal handler for SIGINT (Ctrl+C) during heredoc input.
 * * This handler sets the global exit status to 130, prints a newline to 
 * maintain terminal visual integrity, and closes STDIN. Closing STDIN 
 * is a common trick to force active input functions (like readline) 
 * to return NULL/EOF, effectively breaking the heredoc loop.
 * * @param sig The signal number (SIGINT).
 */
static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_status = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

/**
 * @brief Configures signal behavior specifically for heredoc processing.
 * * Sets up SIGINT to be handled by handle_sigint_heredoc to allow the user 
 * to cancel heredoc input. SIGQUIT (Ctrl+\) is explicitly ignored, as 
 * it should not affect the shell during input collection. This setup 
 * ensures the heredoc remains interactive but interruptible.
 */
void	heredoc_signal_setup(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
