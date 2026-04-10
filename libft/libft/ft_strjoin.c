/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:09:29 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 12:05:48 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and returns a new string,
 * which is the result of the concatenation of s1 and s2.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return A new string which is the concatenation of s1 and s2.
 * Returns NULL if the allocation fails or if either s1 or s2 is NULL.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*temp_dest;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_dest = len_s1 + len_s2;
	dest = (char *)malloc(len_dest + 1);
	if (dest == NULL)
		return (NULL);
	temp_dest = dest;
	while (len_s1-- > 0)
		*temp_dest++ = *s1++;
	while (len_s2-- > 0)
		*temp_dest++ = *s2++;
	*temp_dest = '\0';
	return (dest);
}
