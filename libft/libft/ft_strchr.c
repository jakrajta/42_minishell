/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/12 16:37:51 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/12 16:37:51 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of character c 
 * (converted to unsigned char) in the string pointed to by str.

 * @param str Pointer to the null-terminated string to be searched.
 * @param c Character to locate (converted to unsigned char).
 * @return Pointer to the first occurrence of c in str, or NULL 
 * if c is not found.
 * If c is '\0', returns a pointer to the null terminator of str.
 */
char	*ft_strchr(const char *str, int c)
{
	const char		*temp;
	unsigned char	ch;

	temp = str;
	ch = c;
	while (*temp != '\0')
	{
		if (*temp == ch)
			return ((char *)temp);
		temp++;
	}
	if (ch == '\0')
		return ((char *)temp);
	return (NULL);
}
