/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:24:20 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 12:18:48 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies up to destsize - 1 characters 
 * from the NUL-terminated string src to dest,
 * NUL-terminating the result.
 * @param dest Destination buffer where the content is copied.
 * @param src Source string to copy from.
 * @param destsize Size of the destination buffer.
 * @return The total length of the string it tried 
 * to create — length of src.
 * If the return value is >= destsize, truncation occurred.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	char		*temp_dest;
	const char	*temp_src;
	size_t		n;

	temp_dest = dest;
	temp_src = src;
	n = destsize;
	if (n > 0)
	{
		n--;
		while (*temp_src != '\0' && n > 0)
		{
			*temp_dest = *temp_src;
			temp_src++;
			temp_dest++;
			n--;
		}
		*temp_dest = '\0';
	}
	while (*temp_src != '\0')
		temp_src++;
	return (temp_src - src);
}
