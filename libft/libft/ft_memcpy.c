/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:17:59 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 11:54:00 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 * 
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory area dest.
 * @note The memory areas must not overlap. For overlapping memory
 *  areas, use ft_memmove.
 * @note If both dest and src are NULL, the function returns NULL.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	unsigned const char	*temp_src;

	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	if (!temp_dest && !temp_src)
		return (NULL);
	while (n > 0)
	{
		*temp_dest = *temp_src;
		temp_dest++;
		temp_src++;
		n--;
	}
	return (dest);
}
