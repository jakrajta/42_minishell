/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:31:54 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 12:16:06 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a given character is present in a given set of characters.
 *
 * @param c The character to check.
 * @param set The set of characters to compare against.
 * @return 1 if the character is found in the set, 0 otherwise.
 */
static int	check_set_with_char(char c, char const *set)
{
	char const	*temp_set;

	temp_set = set;
	while (*temp_set != '\0')
	{
		if (*temp_set == c)
			return (1);
		temp_set++;
	}
	return (0);
}

/**
 * @brief Allocates and returns a copy of the string s1 with the characters
 * specified in set removed from the beginning and the end.
 * @param s1 The string to be trimmed.
 * @param set The set of characters to remove from the string.
 * @return A new trimmed string, or NULL if allocation fails or s1/set is NULL.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*temp_s1;
	char		*dest;
	char		*temp_dest;
	const char	*end;
	size_t		middle_s1;

	if (s1 == NULL || set == NULL)
		return (NULL);
	temp_s1 = s1;
	while (*temp_s1 != '\0' && check_set_with_char(*temp_s1, set) == 1)
		temp_s1++;
	end = s1 + ft_strlen(s1);
	while (end > temp_s1 && check_set_with_char(*(end - 1), set) == 1)
		end--;
	middle_s1 = end - temp_s1;
	dest = (char *)malloc(middle_s1 + 1);
	if (dest == NULL)
		return (NULL);
	temp_dest = dest;
	while (temp_s1 < end)
		*temp_dest++ = *temp_s1++;
	*temp_dest = '\0';
	return (dest);
}
