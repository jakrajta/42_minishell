#include "minishell.h"

/**
 * @brief Identifies the type of a given token string.
 * * This function categorizes a raw string into a specific token type 
 * (PIPE, REDIRECTION, HEREDOC, etc.) based on its content. It prioritizes 
 * two-character operators (>> and <<) before checking single-character 
 * operators. If no operator is matched, the token is classified as a WORD.
 * * @param token The string representing a single token from the lexer.
 * @return t_token The corresponding enum value (PIPE, APPEND, HEREDOC, 
 * REDIR_OUT, REDIR_IN, or WORD).
 */
t_token	get_token_type(char *token)
{
	if (ft_strncmp(token, ">>", 3) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (HEREDOC);
	if (*token == '|')
		return (PIPE);
	if (*token == '>')
		return (REDIR_OUT);
	if (*token == '<')
		return (REDIR_IN);
	return (WORD);
}
