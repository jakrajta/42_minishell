/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/13 13:17:14 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/13 13:17:14 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and copies a single word from the string.
 * 
 * @param s Pointer to the current position in the string. 
 * After copying, the pointer is advanced past the word.
 * @param c Delimiter character that separates words.
 * @return Pointer to the newly allocated word string,
 *  or NULL if allocation fails.
 */
static char	*word_allocate_and_copy(const char **s, char c)
{
	const char	*word_start;
	char		*word;
	size_t		word_len;

	word_start = *s;
	word_len = 0;
	while ((*s)[word_len] != '\0' && (*s)[word_len] != c)
		word_len++;
	word = malloc(sizeof(char) * (word_len + 1));
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, word_start, word_len);
	word[word_len] = '\0';
	(*s) += word_len;
	return (word);
}

/**
 * @brief Counts the number of words in the string separated by the delimiter.
 * 
 * @param s Input string to count words in.
 * @param c Delimiter character separating words.
 * @return Number of words found in the string.
 */
static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			count++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (count);
}

/**
 * @brief Frees an array of strings and the array itself.
 * 
 * @param array Array of strings to free.
 */
static void	free_all(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief Fills the pre-allocated array with words parsed from the string.
 *        Frees allocated memory and returns NULL on failure.
 * 
 * @param s Input string to split.
 * @param c Delimiter character.
 * @param words_array Pre-allocated array to fill with word pointers.
 * @return Pointer to the filled array, or NULL if an allocation fails.
 */
static char	**fill_array_with_words(const char *s, char c, char **words_array)
{
	char	**temp_word_array;
	char	*word;

	temp_word_array = words_array;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			word = word_allocate_and_copy(&s, c);
			if (word == NULL)
			{
				free_all(words_array);
				return (NULL);
			}
			*temp_word_array++ = word;
		}
	}
	*temp_word_array = NULL;
	return (words_array);
}

/**
 * @brief Splits the input string into an array of strings 
 * (words) separated by the given delimiter.
 *Each word is dynamically allocated. The resulting array is NULL-terminated.
 * 
 * @param s Input string to split.
 * @param c Delimiter character to split the string by.
 * @return Pointer to a dynamically allocated array of 
 * strings (words), or NULL on failure.
 */
char	**ft_split(const char *s, char c)
{
	char	**words_array;
	int		word_count;
	int		i;
	char	**result;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	words_array = malloc(sizeof(char *) * (word_count + 1));
	if (words_array == NULL)
		return (NULL);
	i = 0;
	while (i <= word_count)
		words_array[i++] = NULL;
	result = fill_array_with_words(s, c, words_array);
	return (result);
}
