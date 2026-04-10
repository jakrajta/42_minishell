#include "minishell.h"

/**
 * @brief Prints a formatted syntax error message and updates shell status.
 * * This function handles the "minishell: syntax error near unexpected token" 
 * message. If the offending token is NULL (e.g., at the end of a line), 
 * it prints 'newline'. Otherwise, it prints the specific token character.
 * It sets the exit status to 2, which is the standard Bash code for syntax errors.
 * * @param shell Pointer to the shell structure to update last_exit_status.
 * @param token The token that caused the syntax error (can be NULL).
 * @return Always returns 1 to signal that a syntax error was found.
 */
static int	error_syntax(t_shell *shell, char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	shell->last_exit_status = 2;
	return (1);
}

/**
 * @brief Scans the token array for structural command line errors.
 * * Performs a comprehensive check of the token sequence before execution:
 * - Prevents starting a command line with a pipe ('|').
 * - Ensures pipes are not followed by NULL or another pipe (e.g., 'ls | |').
 * - Ensures redirections (>, <, >>, <<) are followed by a valid word, 
 * preventing cases like 'ls > |' or 'ls >'.
 * * @param shell Pointer to the shell structure containing all_tokens.
 * @return 0 if the syntax is valid, 1 if an error is detected and reported.
 */
int	check_syntax_error(t_shell *shell)
{
	char	**tok;
	int		i;

	tok = shell->all_tokens;
	if (!tok || !tok[0])
		return (0);
	if (!ft_strncmp(tok[0], "|", 2))
		return (error_syntax(shell, "|"));
	i = -1;
	while (tok[++i])
	{
		if (!ft_strncmp(tok[i], "|", 2))
		{
			if (!tok[i + 1] || !ft_strncmp(tok[i + 1], "|", 2))
				return (error_syntax(shell, tok[i + 1]));
		}
		else if (is_redirection(tok[i]))
		{
			if (!tok[i + 1] || !ft_strncmp(tok[i + 1], "|", 2)
				|| is_redirection(tok[i + 1]))
				return (error_syntax(shell, tok[i + 1]));
		}
	}
	return (0);
}
