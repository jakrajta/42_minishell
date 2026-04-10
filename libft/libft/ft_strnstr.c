/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:32:14 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 12:14:04 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of the null-terminated string s2 
 * in the string s1, where not more than n characters are searched.
 * Characters that appear after a '\0' are not searched.
 * 
 * @param s1 The string to be searched.
 * @param s2 The substring to search for.
 * @param n The maximum number of characters to search.
 * @return If s2 is an empty string, s1 is returned; if s2 occurs nowhere in s1,
 * NULL is returned; otherwise a pointer to the first character of the first
 * occurrence of s2 is returned.
 */
char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	const char	*temp_s1;
	const char	*temp_s2;
	size_t		len;

	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1 != '\0' && n > 0)
	{
		temp_s1 = s1;
		temp_s2 = s2;
		len = n;
		while (*temp_s1 != '\0' && *temp_s2 == *temp_s1 && len > 0)
		{
			temp_s1++;
			temp_s2++;
			len--;
		}
		if (*temp_s2 == '\0')
			return ((char *)s1);
		s1++;
		n--;
	}
	return (NULL);
}
