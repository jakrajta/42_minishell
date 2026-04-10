#include "minishell.h"

/**
 * @brief Allocates and initializes a new redirection structure.
 * * Based on the operator token (e.g., '>', '>>', '<', '<<'), it determines 
 * the redirection type and sets default values for its members. 
 * If the token is not a valid redirection operator, it returns NULL.
 * * @param token The operator string to be identified.
 * @return t_redir* Pointer to the new redirection structure, 
 * or NULL on allocation failure or invalid token type.
 */
t_redir	*init_redir_struct(char *token)
{
	t_redir	*redir;
	t_token	type;

	type = get_token_type(token);
	if (type == WORD || type == PIPE)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->tok_type = type;
	redir->file = NULL;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}
