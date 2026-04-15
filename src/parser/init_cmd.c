#include "minishell.h"

/**
 * @brief Calculates the required size for the command's tokens array.
 * * Accounts for word splitting: tokens with '=' or quotes count as one,
 * while others are counted based on how many words they split into.
 * Redirections and their filenames are skipped during counting.
 * * @param tokens Array of raw tokens.
 * @param i Starting index in the tokens array.
 * @return int The total number of real tokens (strings) for the command.
 */
static int	count_real_tokens(char **tokens, int i)
{
	int	len;

	len = 0;
	while (tokens[i] && (get_token_type(tokens[i]) != PIPE))
	{
		if (is_redirection(tokens[i]))
		{
			if (tokens[i + 1])
				i++;
		}
		else if (get_token_type(tokens[i]) == WORD)
		{
			if (ft_strchr(tokens[i], '=') || tokens[i][0] == '\"'
			|| tokens[i][0] == '\'')
				len++;
			else
				len += count_words(tokens[i], SEPARATOR);
		}
		else
			len++;
		i++;
	}
	return (len);
}

/**
 * @brief Allocates and initializes a new command structure.
 * * Sets default values, calculates necessary memory for tokens, and
 * calls fill_tokens_redirs to populate the structure.
 * * @param raw_tokens Array of tokens from the lexer/expander.
 * @param i Pointer to the current index in the raw_tokens array.
 * @return t_cmd* Pointer to the newly created command, or NULL on failure.
 */
t_cmd	*init_cmd(char **raw_tokens, int *i)
{
	t_cmd	*cmd;
	int		len;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->tokens_count = 0;
	cmd->valid_path = NULL;
	cmd->skip_exec = 0;
	cmd->builtin = B_NONE;
	cmd->redir = NULL;
	cmd->next = NULL;
	len = count_real_tokens(raw_tokens, *i);
	cmd->tokens = malloc(sizeof(char *) * (len + 1));
	if (!cmd->tokens)
		return (free(cmd), NULL);
	fill_tokens_redirs(cmd, raw_tokens, i);
	return (cmd);
}
