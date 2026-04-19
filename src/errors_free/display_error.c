#include "minishell.h"

/**
 * @brief Prints a formatted system error message to stderr.
 *
 * This function constructs a standard shell error message in the format:
 * "minishell: [cmd]: [arg]: [msg]". All components are optional.
 *
 * @param cmd The name of the command that failed (can be NULL).
 * @param arg The argument that caused the error (can be NULL).
 * @param msg The error message description (can be NULL).
 * @return Returns 1, useful for returning in error conditions.
 */
int	sys_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

/**
 * @brief Prints a simple error message to stderr.
 *
 * Prints the provided message followed by a newline character to the 
 * standard error stream.
 *
 * @param msg The error message to be displayed.
 * @return Returns 1, useful for returning in error conditions.
 */
int	display_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

/**
 * @brief Displays a warning message when a here-document is terminated by EOF.
 *
 * This function notifies the user that the here-document input was ended 
 * prematurely by an EOF (Ctrl+D) instead of the expected delimiter.
 *
 * @param delimiter The delimiter string that was expected.
 * @return Returns 1, useful for returning in error or warning conditions.
 */
int	display_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	return (1);
}
