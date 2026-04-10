#include "minishell.h"

/**
 * @brief Validates if a string represents a valid numeric integer.
 * * Checks for an optional leading '+' or '-' sign and ensures all 
 * remaining characters are digits.
 * * @param str The string to validate.
 * @return int Returns 1 if valid numeric format, 0 otherwise.
 */
static int	is_number(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

/**
 * @brief Checks if a number exceeds the limits of long long.
 * * Compares the current parsed number against LLONG_MAX or LLONG_MIN
 * equivalent (LLONG_MAX + 1 for negative) to prevent overflow.
 * * @param n The unsigned long long value parsed so far.
 * @param sign The sign of the number (1 for positive, -1 for negative).
 * @return int Returns 1 if the value overflows, 0 otherwise.
 */
static int	exceeded_llong(unsigned long long n, int sign)
{
	if (sign == 1 && (n > (unsigned long long)LLONG_MAX))
		return (1);
	if (sign == -1 && (n > (unsigned long long)LLONG_MAX + 1))
		return (1);
	return (0);
}

/**
 * @brief Custom atoi that handles long long and detects overflow.
 * * Converts a string to a long long integer. If the conversion fails due 
 * to an overflow, the function returns an error signal.
 * * @param str The string to convert.
 * @param result Pointer to store the converted long long value.
 * @return int Returns 1 on success, 0 if overflow occurs.
 */
static int	exit_ll_atoi(const char *str, long long *result)
{
	unsigned long long	number;
	int					sign;

	number = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		number = number * 10 + (*str - '0');
		if (exceeded_llong(number, sign) == 1)
			return (0);
		str++;
	}
	*result = number * sign;
	return (1);
}

/**
 * @brief Cleans up shell resources and terminates the process.
 * * Clears Readline history, frees all allocated shell memory, and 
 * calls exit() with the provided status.
 * * @param shell Pointer to the shell structure.
 * @param status The exit status code to terminate with.
 */
static void	cleanup_and_exit(t_shell *shell, int status)
{
	rl_clear_history();
	free_shell(&shell);
	exit(status);
}

/**
 * @brief Executes the exit built-in command.
 * * Handles termination of the shell. Validates the number of arguments 
 * and ensures the exit code is a valid numeric value. 
 * - If no args: exits with last exit status.
 * - If non-numeric arg: prints error and exits with 2.
 * - If too many args: prints error and does NOT exit (returns 1).
 * * @param cmd Pointer to the command structure.
 * @param shell Pointer to the shell structure.
 * @return int Returns 1 if "too many arguments",
 * otherwise terminates the process.
 */
int	execute_exit(t_cmd *cmd, t_shell *shell)
{
	long long	exit_code;

	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	if (cmd->tokens_count == 1)
	{
		cleanup_and_exit(shell, shell->last_exit_status);
	}
	if (is_number(cmd->tokens[1]) == 0
		|| exit_ll_atoi(cmd->tokens[1], &exit_code) == 0)
	{
		sys_error(cmd->tokens[0], cmd->tokens[1],
			"numeric argument required");
		cleanup_and_exit(shell, 2);
	}
	if (cmd->tokens_count > 2)
	{
		shell->last_exit_status = sys_error(cmd->tokens[0], NULL,
				"too many arguments");
		return (1);
	}
	cleanup_and_exit(shell, (unsigned char)exit_code);
	return (0);
}
