/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/13 16:00:29 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/13 16:00:29 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares up to n characters of the string s1 to those of the string s2.
 * @param s1 First null-terminated string to compare.
 * @param s2 Second null-terminated string to compare.
 * @param n Maximum number of characters to compare.
 * @return An integer less than, equal to, or 
 * greater than zero if s1 (or the first n characters thereof)
 * s found, respectively, to be less than,
 * to match, or be greater than s2.
 */
int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	if (n == 0)
		return (0);
	while ((*s1 == *s2 && *s1 != '\0' && *s2 != '\0') && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
