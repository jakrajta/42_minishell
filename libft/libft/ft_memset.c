/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/30 14:23:16 by jakrajic          #+#    #+#             */
/*   Updated: 2025/05/30 14:23:16 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills the first n bytes of the memory area
 * pointed \ to by str with the constant byte c.
 * 
 * @param str Pointer to the memory area to fill.
 * @param c Byte value to set (converted to unsigned char).
 * @param n Number of bytes to be set to the value.
 * @return Pointer to the memory area str.
 */
void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*p_str;

	p_str = str;
	while (n > 0)
	{
		*p_str = (unsigned char)c;
		p_str++;
		n--;
	}
	return (str);
}
