#include "minishell.h"

/**
 * @brief Checks if a string is a valid '-n' flag.
 * * A valid flag must start with '-' followed by at least one 'n'.
 * Subsequent characters must only be 'n' (e.g., -n, -nn, -nnn).
 * * @param str The string to be checked.
 * @return int Returns 1 if it's a valid flag, 0 otherwise.
 */
static int	is_nflag(char *str)
{
	if (!str || *str != '-' || *(str + 1) != 'n')
		return (0);
	str += 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

/**
 * @brief Executes the echo built-in command.
 * * Outputs the given tokens to standard output. It handles the '-n' flag,
 * which suppresses the trailing newline. Multiple '-n' flags or flags
 * with multiple 'n's (e.g., -nnnn) are also handled.
 * * @param cmd Pointer to the command structure containing 
 * tokens and token count.
 * @return int Always returns 0 to indicate successful execution.
 */
int	execute_echo(t_cmd *cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	while (cmd->tokens[i] && is_nflag(cmd->tokens[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd->tokens[i])
	{
		write(1, cmd->tokens[i], ft_strlen(cmd->tokens[i]));
		if (i < (cmd->tokens_count - 1))
			write (1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
