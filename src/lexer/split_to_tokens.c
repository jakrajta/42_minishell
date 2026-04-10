#include "minishell.h"

static char	*skip_to_end(char *str)
{
	char	quote;

	quote = 0;
	while (*str && ((!is_in_set(SEPARATOR, *str)
				&& !is_in_set(METACHARS, *str)) || quote != 0))
	{
		if (quote == 0 && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		str++;
	}
	return (str);
}

static int	count_tokens(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_in_set(SEPARATOR, *str))
			str++;
		if (*str)
		{
			count++;
			if (is_in_set(METACHARS, *str))
			{
				if (is_double_redir(str))
					str += 2;
				else
					str++;
			}
			else
				str = skip_to_end(str);
		}
	}
	return (count);
}

static int	token_len(char *str)
{
	int	quote;
	int	len;

	quote = 0;
	len = 0;
	if (is_double_redir(str))
		return (2);
	if (is_in_set(METACHARS, *str))
		return (1);
	while (*str)
	{
		if ((is_in_set(SEPARATOR, *str)
				|| is_in_set(METACHARS, *str)) && quote == 0)
			break ;
		if ((*str == '\'' || *str == '\"') && quote == 0)
			quote = *str;
		else if (quote != 0 && *str == quote)
			quote = 0;
		len++;
		str++;
	}
	return (len);
}

/**
 * @brief Tokenizes an input string into an array of strings (tokens).
 * * This function mimics the behavior of a shell lexer by splitting the 
 * input based on separators and metacharacters, while respecting 
 * single and double quotes.
 * * 1. Counts the number of tokens to allocate the pointer array.
 * 2. Iteratively extracts each token while handling special shell 
 * characters (|, <, >, <<, >>).
 * 3. Handles memory cleanup if allocation fails during the process.
 * * @param str The raw input string from the command line.
 * @return A NULL-terminated array of strings, or NULL on allocation failure.
 */
static char	*get_token(char **str)
{
	int		len;
	char	*one_token;
	char	*token_ptr;

	len = token_len(*str);
	one_token = malloc(sizeof(char) * (len + 1));
	if (!one_token)
		return (NULL);
	token_ptr = one_token;
	while (len > 0)
	{
		*token_ptr++ = *(*str)++;
		len--;
	}
	*token_ptr = '\0';
	return (one_token);
}

/**
 * @internal
 * @brief Identifies the boundaries of a single token and extracts it.
 * * Moves the pointer forward in the source string as it consumes characters.
 * Handles both regular words and metacharacters.
 * * @param str Pointer to the current position in the input string.
 * @return An allocated string containing the token.
 */
char	**split_to_tokens(char *str)
{
	char	**tokens_ptr_array;
	char	**temp;

	tokens_ptr_array = malloc(sizeof(char *) * (count_tokens(str) + 1));
	if (!tokens_ptr_array)
		return (NULL);
	temp = tokens_ptr_array;
	while (*str)
	{
		while (*str && is_in_set(SEPARATOR, *str) == 1)
			str++;
		if (*str)
		{
			*temp = get_token(&str);
			if (!*temp)
				return (free_array(tokens_ptr_array), NULL);
			temp++;
		}
	}
	*temp = NULL;
	return (tokens_ptr_array);
}
