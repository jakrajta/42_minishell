/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:21:23 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 11:55:01 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 *The memory areas may overlap: copying takes place as though the bytes
 *in src are first copied into a temporary array that does not overlap 
 src or dest,
 *and the bytes are then copied from the temporary array to dest.
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory area dest.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	if (dest == src || n == 0)
		return (dest);
	if (temp_dest < temp_src)
	{
		while (n-- > 0)
		{
			*temp_dest++ = *temp_src++;
		}
	}
	else
	{
		temp_dest += n;
		temp_src += n;
		while (n-- > 0)
			*--temp_dest = *--temp_src;
	}
	return (dest);
}
