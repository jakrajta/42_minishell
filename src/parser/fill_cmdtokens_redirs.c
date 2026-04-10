#include "minishell.h"

/**
 * @brief Appends a redirection structure 
 * to the end of the command's linked list.
 * * @param redir Pointer to the redirection structure to add.
 * @param cmd Pointer to the command structure containing the redirection list.
 */
static void	add_redir_to_cmd(t_redir *redir, t_cmd *cmd)
{
	t_redir	*current;

	if (!cmd->redir)
	{
		cmd->redir = redir;
		return ;
	}
	current = cmd->redir;
	while (current->next)
		current = current->next;
	current->next = redir;
}

/**
 * @brief Initializes and fills a redirection structure from tokens.
 * * Handles error checking for ambiguous redirects 
 * (empty filename after expansion).
 * If an error occurs, sets cmd->skip_exec to 1.
 * * @param cmd Pointer to the current command structure.
 * @param tokens Array of strings (tokens).
 * @param current_i Pointer to the current index in the tokens array.
 * @return int 1 if successful, 0 if an error occurs or no filename is present.
 */
static int	fill_redir_list(t_cmd *cmd, char **tokens, int *current_i)
{
	t_redir	*redir;

	if (!tokens[*current_i + 1])
		return (0);
	redir = init_redir_struct(tokens[*current_i]);
	if (!redir)
		return (0);
	if (tokens[*current_i + 1][0] == '\0')
	{
		cmd->skip_exec = 1;
		sys_error(NULL, tokens[*current_i + 1], "ambiguous redirect");
		free(redir);
		return (0);
	}
	redir->file = ft_strdup(tokens[*current_i + 1]);
	if (!redir->file)
		return (free(redir), 0);
	remove_quotes(redir->file);
	add_redir_to_cmd(redir, cmd);
	*current_i += 2;
	return (1);
}

/**
 * @brief Processes a WORD token and adds it to the command's tokens array.
 * * If the token contains an assignment (=) or is quoted, it is added as a 
 * single string after removing quotes. Otherwise, it is split into multiple 
 * tokens based on SEPARATOR (word splitting).
 * * @param cmd Pointer to the command structure.
 * @param token The string token to process.
 * @param c Pointer to the current index in the cmd->tokens array.
 */
static void	handle_word(t_cmd *cmd, char *token, int *c)
{
	char	**splited_word;
	int		j;

	if (ft_strchr(token, '=') || ft_strchr(token, '\"')
		|| ft_strchr(token, '\''))
	{
		remove_quotes(token);
		cmd->tokens[(*c)++] = ft_strdup(token);
	}
	else
	{
		splited_word = general_split(token, SEPARATOR);
		j = 0;
		while (splited_word && splited_word[j])
			cmd->tokens[(*c)++] = splited_word[j++];
		free(splited_word);
	}
}

/**
 * @brief Iterates through tokens to fill command tokens and redirections.
 * * Stops when a PIPE is encountered or the end of tokens is reached.
 * Also determines if the command is a builtin.
 * * @param cmd Pointer to the command structure to be filled.
 * @param tokens Array of tokens from the lexer.
 * @param i Pointer to the current index in the raw tokens array.
 */
void	fill_tokens_redirs(t_cmd *cmd, char **tokens, int *i)
{
	int	c;

	c = 0;
	while (tokens[*i])
	{
		if (get_token_type(tokens[*i]) == PIPE)
			break ;
		else if (is_redirection(tokens[*i]))
		{
			if (!fill_redir_list(cmd, tokens, i))
				break ;
		}
		else if (get_token_type(tokens[*i]) == WORD)
		{
			handle_word(cmd, tokens[*i], &c);
			(*i)++;
		}
		else
			(*i)++;
	}
	cmd->tokens[c] = NULL;
	cmd->tokens_count = c;
	if (c > 0)
		cmd->builtin = get_builtin_type(cmd->tokens[0]);
}
