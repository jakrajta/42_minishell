/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:12 by jakrajic          #+#    #+#             */
/*   Updated: 2026/02/12 21:05:47 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends the NUL-terminated string src to the end of dest.
 * It will append at most destsize - strlen(dest) - 1 bytes, 
 * NUL-terminating the result.
 * @param dest Destination buffer.
 * @param src Source string to append.
 * @param destsize Full size of the destination buffer.
 * @return The total length of the string it tried to create:
 * the initial length of dest plus the length of src.
 * If the return value is >= destsize, truncation occurred.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	char		*temp_dest;
	const char	*temp_src;
	size_t		n;
	size_t		dlen;

	temp_dest = dest;
	temp_src = src;
	n = destsize;
	while (n-- && *temp_dest != '\0')
		temp_dest++;
	dlen = temp_dest - dest;
	n = destsize - dlen;
	if (n == 0)
		return (dlen + ft_strlen(src));
	while (*temp_src)
	{
		if (n > 1)
		{
			*temp_dest++ = *temp_src;
			n--;
		}
		temp_src++;
	}
	*temp_dest = '\0';
	return (dlen + (temp_src - src));
}
