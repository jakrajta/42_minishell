#include "minishell.h"

/**
 * @brief Constructs a linked list of command structures from all lexer tokens.
 * * This function iterates through the global array of 
 * tokens (shell->all_tokens)
 * and organizes them into individual t_cmd structures. It handles the logic
 * for piping by creating a new command node every time a PIPE token is
 * encountered.
 * * @param shell Pointer to the main shell structure containing all tokens.
 * @return t_cmd* Pointer to the first command in the linked list, 
 * or NULL if no tokens exist or an allocation fails.
 */
t_cmd	*fill_cmd_list(t_shell *shell)
{
	t_cmd	*current;
	int		i;

	if (!shell->all_tokens || !shell->all_tokens[0])
		return (NULL);
	i = 0;
	shell->cmd = init_cmd(shell->all_tokens, &i);
	if (!shell->cmd)
		return (NULL);
	current = shell->cmd;
	while (shell->all_tokens[i] && get_token_type(shell->all_tokens[i]) == PIPE)
	{
		i++;
		current->next = init_cmd(shell->all_tokens, &i);
		if (!current->next)
			break ;
		current = current->next;
	}
	return (shell->cmd);
}
