/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/12 11:34:17 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/12 11:34:17 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Searches for the first occurrence of the character
 *  c (converted to unsigned char) 
 * in the first n bytes of the memory area pointed to by s.
 * @param s Pointer to the memory area to be searched.
 * @param c Character to search for (converted to unsigned char).
 * @param n Number of bytes to search.
 * @return Pointer to the matching byte or NULL if the character
 *  does not occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*temp_s;
	unsigned char		ch;

	temp_s = (const unsigned char *)s;
	ch = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (n > 0)
	{
		if (*temp_s == ch)
			return ((void *)temp_s);
		temp_s++;
		n--;
	}
	return (NULL);
}
