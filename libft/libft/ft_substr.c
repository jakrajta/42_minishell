/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:19:27 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 12:17:21 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and returns a substring from the string s.
 *        The substring begins at index start and is of maximum length len.
 * 
 * @param s The source string.
 * @param start The starting index of the substring in s.
 * @param len The maximum length of the substring.
 * @return A pointer to the newly allocated substring.
 * Returns an empty string if start is greater than the length of s.
 * Returns NULL if memory allocation fails or s is NULL.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*temp_substr;
	size_t	len_substr;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len <= ft_strlen(s))
		len_substr = len;
	else
		len_substr = ft_strlen(s) - start;
	substr = (char *)malloc(len_substr + 1);
	if (substr == NULL)
		return (NULL);
	temp_substr = substr;
	while (len_substr-- > 0)
	{
		*temp_substr++ = *(s + start);
		start++;
	}
	*temp_substr = '\0';
	return (substr);
}
