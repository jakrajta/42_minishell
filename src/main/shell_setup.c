#include "minishell.h"

/**
 * @brief Toggles the ECHOCTL flag in the terminal settings.
 *
 * ECHOCTL determines whether control characters (like Ctrl+C) are echoed 
 * as visible characters (e.g., ^C) in the terminal output. 
 * Disabling this makes the terminal output cleaner during shell operation.
 *
 * @param enable If non-zero, enables the ECHOCTL flag; if zero, disables it.
 */
void	toggle_echoctl(int enable)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
		return ;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	if (enable)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * @brief Handles the incrementation of the SHLVL environment variable.
 * * 1. Fetches the current SHLVL value from the environment copy.
 * 2. Increments the value or sets it to 1 if it doesn't exist.
 * 3. Converts the new level back to a string using ft_itoa.
 * 4. Updates the environment structure with the new level.
 * 5. Frees the temporary string created by ft_itoa.
 * @param shell Pointer to the main shell structure.
 */
void	handle_shlvl(t_shell *shell)
{
	char	*value;
	int		num;

	if (!shell || !shell->env || !shell->env->env_copy)
		return ;
	value = get_env_value("SHLVL", shell->env->env_copy);
	if (value)
		num = ft_atoi(value) + 1;
	else
		num = 1;
	value = ft_itoa(num);
	if (!value)
		return ;
	update_env_value("SHLVL", value, shell->env);
	free(value);
}

/**
 * @brief Initializes the shell environment and terminal settings.
 *
 * Saves the original terminal attributes to ensure they can be restored later,
 * disables the ECHOCTL flag to prevent "^C" from appearing on the screen 
 * during interactive use, updates the shell level, and configures signal handlers.
 *
 * @param shell Pointer to the shell structure to be initialized.
 */
void	shell_setup(t_shell *shell)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &shell->original_term) == -1)
			return ;
		toggle_echoctl(0);
	}
	handle_shlvl(shell);
	signal_setup();
}
