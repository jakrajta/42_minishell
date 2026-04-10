#include "minishell.h"

/**
 * @brief Finalizes tokens by performing expansion. Quotes remain and
 * are striped in fce init_cmd( handle_words)
 * * This function iterates through the null-terminated array of tokens to:
 * 1. Expand environment variables (unless the token is explicitly 
 * protected by leading single quotes).
 * * @param tokens A NULL-terminated array of strings (tokens).
 * @param shell Pointer to the main shell structure for context.
 */
void	finalize_tokens(char **tokens, t_shell *shell)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = expand_all(tokens[i], shell);
		i++;
	}
}
