#include "minishell.h"

/**
 * @brief Checks if a string starts with a double redirection 
 * operator (>> or <<).
 *
 * @param str The string to check.
 * @return Returns 1 if it is a double redirection, 0 otherwise.
 */
int	is_double_redir(char *str)
{
	if (!str || !*str || !*(str + 1))
		return (0);
	return ((*str == '>' && *(str + 1) == '>')
		|| (*str == '<' && *(str + 1) == '<'));
}

/**
 * @brief Checks if a character exists within a given character set.
 *
 * @param set A string containing the set of allowed characters.
 * @param c The character to search for.
 * @return Returns 1 if found, 0 otherwise.
 */
int	is_in_set(char *set, char c)
{
	return (c != '\0' && ft_strchr(set, c) != NULL);
}

/**
 * @brief Determines if a token represents a redirection.
 *
 * Uses the token type to distinguish redirections (<, >, >>, <<) 
 * from regular words or pipes.
 *
 * @param token The token string to analyze.
 * @return Returns 1 if the token is a redirection, 0 otherwise.
 */
int	is_redirection(char *token)
{
	t_token	type;

	if (!token)
		return (0);
	type = get_token_type(token);
	if (type == WORD || type == PIPE)
		return (0);
	return (1);
}

/**
 * @brief Compares two strings lexicographically.
 *
 * A custom implementation of strcmp that handles NULL pointers safely.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return 0 if strings are equal, otherwise the difference between 
 * the first non-matching characters.
 */
int	my_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/**
 * @brief Counts the number of elements in a NULL-terminated array of strings.
 *
 * @param array The NULL-terminated array of pointers.
 * @return The total count of elements.
 */
int	tokens_count(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return (0);
	while (*array)
	{
		count++;
		array++;
	}
	return (count);
}
