#include "minishell.h"

/**
 * @brief Checks for unclosed quotes in the token array.
 * * Iterates through each token and its characters to ensure that every 
 * opening quote (' or ") has a corresponding closing quote. It tracks 
 * the state using the 'quote' variable to handle nested quotes of the 
 * opposite type (e.g., "it's" is valid).
 *
 * @param tokens The array of strings (tokens) to be checked.
 * @param shell Pointer to the shell structure for updating the exit status.
 * @return 0 if all quotes are properly closed, 1 if a syntax error is detected.
 * * @note If an unclosed quote is found, it prints a syntax error message 
 * and sets shell->last_exit_status to 2.
 */
int	check_quotes_error(char **tokens, t_shell *shell)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	while (tokens && tokens[i])
	{
		quote = 0;
		j = 0;
		while (tokens[i][j])
		{
			if ((tokens[i][j] == '\"' || tokens[i][j] == '\'') && quote == 0)
				quote = tokens[i][j];
			else if (tokens[i][j] == quote && quote != 0)
				quote = 0;
			j++;
		}
		i++;
	}
	if (quote == 0)
		return (0);
	sys_error(NULL, NULL, "syntax error near unexpected token `newline'");
	shell->last_exit_status = 2;
	return (1);
}
