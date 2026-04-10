#include "minishell.h"

/**
 * @brief Counts the number of words in a string based on a set of delimiters.
 * * Iterates through the string and identifies the start of new words by 
 * checking transitions from a delimiter to a non-delimiter character.
 * * @param str The input string to analyze.
 * @param set A string containing delimiter characters.
 * @return The total count of words found.
 */
int	count_words(char *str, char *set)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*str)
	{
		if (!is_in_set(set, *str) && i == 0)
		{
			i = 1;
			count++;
		}
		else if (is_in_set(set, *str))
			i = 0;
		str++;
	}
	return (count);
}

/**
 * @brief Measures the length of a single word until the next delimiter.
 * * Helper function to calculate the number of bytes needed for a specific word
 * segment, excluding any characters from the delimiter set.
 * * @param str Pointer to the start of the word.
 * @param set A string containing delimiter characters.
 * @return The number of characters in the word.
 */
static int	count_word_len(char *str, char *set)
{
	int	len;

	len = 0;
	while (*str && !is_in_set(set, *str))
	{
		str++;
		len++;
	}
	return (len);
}

/**
 * @brief Splits a string into an array of strings based on a set of delimiters.
 * * A versatile split function that extracts all segments separated by any 
 * character in 'set'. It handles multiple delimiters in a row and returns 
 * a NULL-terminated array. Uses a stored original pointer for safe memory 
 * cleanup in case of allocation failure.
 * * @param str The input string to be split.
 * @param set A string containing all characters to be treated as delimiters.
 * @return A NULL-terminated array of strings, or NULL if allocation fails.
 */
static char	*get_word(char *str, char *set)
{
	int		len;
	char	*one_word;
	char	*temp;

	len = count_word_len(str, set);
	one_word = malloc(sizeof(char) * (len + 1));
	if (!one_word)
		return (NULL);
	temp = one_word;
	while (*str && !is_in_set(set, *str))
		*temp++ = *str++;
	*temp = '\0';
	return (one_word);
}

/**
 * @brief Splits a string into an array of strings based on a set of delimiters.
 * * A versatile split function that extracts all segments separated by any 
 * character in 'set'. It handles multiple delimiters in a row and returns 
 * a NULL-terminated array. If any allocation fails, it frees all previously 
 * allocated memory using free_array.
 * * @param str The input string to be split.
 * @param set A string containing all characters to be treated as delimiters.
 * @return char** A NULL-terminated array of strings, 
 * or NULL if allocation fails.
 */
char	**general_split(char *str, char *set)
{
	char	**words_array;
	char	**result;
	int		word_len;

	words_array = malloc(sizeof(char *) * (count_words(str, set) + 1));
	if (!words_array)
		return (NULL);
	result = words_array;
	while (*str)
	{
		while (*str && is_in_set(set, *str))
			str++;
		if (*str)
		{
			word_len = count_word_len(str, set);
			*words_array = get_word(str, set);
			if (!*words_array)
				return (free_array(result), NULL);
			str += word_len;
			words_array++;
		}
	}
	*words_array = NULL;
	return (result);
}
