#include "minishell.h"

/**
 * @brief Replaces a variable placeholder in a string with its actual value.
 * * This function takes a token, cuts out the variable name 
 * starting at index 'i',
 * and replaces it with the provided 'value'. It handles the memory by freeing
 * the old token and returning a newly allocated string.
 * * @param token The original string containing the variable.
 * @param i The starting index of the '$' character.
 * @param var_len Total length of the variable to be replaced (including '$').
 * @param value The string to be inserted in place of the variable.
 * @return A newly allocated string with the replaced value, or NULL on failure.
 */
static char	*replace_at_index(char *token, int i, int var_len, char *value)
{
	char	*before_name;
	char	*after_name;
	char	*new_token;

	if (!token)
		return (NULL);
	if (!value)
		value = "";
	before_name = ft_substr(token, 0, i);
	after_name = ft_strdup(token + i + var_len);
	new_token = triple_strjoin(before_name, value, after_name);
	free(before_name);
	free(after_name);
	free(token);
	return (new_token);
}

/**
 * @brief Logic for handling the expansion of a single environment variable.
 * * Identifies the variable name (or the special '?' variable), retrieves its 
 * value from the shell environment, and calls replace_at_index to update 
 * the token. It also updates the index 'i' to point after the inserted value.
 * * @param token The current token being processed.
 * @param i Pointer to the current index in the token string.
 * @param shell Pointer to the shell structure (for env and exit status).
 * @return The updated token string with the expanded variable.
 */
static char	*handle_expansion(char *token, int *i, t_shell *shell)
{
	char	*var_name;
	char	*value;

	if (token[*i + 1] == '?')
	{
		value = ft_itoa(shell->last_exit_status);
		token = replace_at_index(token, *i, 2, value);
		*i += ft_strlen(value);
		free(value);
		return (token);
	}
	var_name = get_env_var_name(&token[*i + 1]);
	if (!var_name)
	{
		(*i)++;
		return (token);
	}
	value = get_env_value(var_name, shell->env->env_copy);
	token = replace_at_index(token, *i, ft_strlen(var_name) + 1, value);
	if (value)
		*i += ft_strlen(value);
	free(var_name);
	return (token);
}

/**
 * @brief Main entry point for variable expansion within a token.
 * * Iterates through the token and expands environment variables (e.g., $VAR).
 * It respects shell quoting rules:
 * - Variables inside single quotes ('$VAR') are NOT expanded.
 * - Variables inside double quotes ("$VAR") ARE expanded.
 * * @param token The raw token from the lexer.
 * @param shell Pointer to the shell structure for context.
 * @return The fully expanded token string.
 */
char	*expand_token(char *token, t_shell *shell)
{
	int	in_single_q;
	int	in_double_q;
	int	i;

	in_single_q = 0;
	in_double_q = 0;
	i = 0;
	while (token && token[i])
	{
		if (token[i] == '\"' && !in_single_q)
			in_double_q = !in_double_q;
		else if (token[i] == '\'' && !in_double_q)
			in_single_q = !in_single_q;
		if (token[i] == '$' && !in_single_q && token[i + 1])
		{
			if (ft_isalnum(token[i + 1]) || token[i + 1] == '_'
				|| token[i + 1] == '?')
			{
				token = handle_expansion(token, &i, shell);
				continue ;
			}
		}
		i++;
	}
	return (token);
}

/**
 * @brief Processes environment variable expansion for all tokens and 
 * stores the result.
 * * This function iterates through a NULL-terminated array of strings (tokens),
 * applying expansion logic (e.g., replacing $VAR with its value) to each.
 * Once all tokens are processed, it updates the shell structure by 
 * assigning the pointer to the processed tokens array to shell->all_tokens.
 * * @param tokens A pointer to the array of strings to be expanded.
 * @param shell A pointer to the main shell structure containing environment 
 * variables and where the final tokens will be stored.
 * * @return void
 */
void	store_expanded_tokens(char **tokens, t_shell *shell)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		tokens[i] = expand_token(tokens[i], shell);
		i++;
	}
	shell->all_tokens = tokens;
}
