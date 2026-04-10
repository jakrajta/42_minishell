/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:39:00 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 11:52:45 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares the first n bytes of two memory areas.
 * 
 * @param s1 Pointer to the first memory area.
 * @param s2 Pointer to the second memory area.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater 
 * than zero if the first n bytes of s1 is found, respectively,
 * to be less than, to match, or be greater than the first n bytes of s2.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*temp_s1;
	unsigned const char	*temp_s2;

	temp_s1 = s1;
	temp_s2 = s2;
	while (n > 0)
	{
		if (*temp_s1 != *temp_s2)
			return ((int)(*temp_s1 - *temp_s2));
		temp_s1++;
		temp_s2++;
		n--;
	}
	return (0);
}
