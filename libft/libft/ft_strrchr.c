/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/13 16:40:22 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/13 16:40:22 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of the character c in the string str.
 * 
 * @param str The string to be searched.
 * @param c The character to locate (converted to unsigned char).
 * @return A pointer to the last occurrence of the character c in the string str,
 * or NULL if the character is not found.
 * If c is '\0', returns a pointer to the null terminator.
 */
char	*ft_strrchr(const char *str, int c)
{
	const char		*temp;
	unsigned char	ch;

	ch = (unsigned char)c;
	temp = str;
	while (*temp != '\0')
		temp++;
	while (temp >= str)
	{
		if (*temp == ch)
			return ((char *)temp);
		temp--;
	}
	return (NULL);
}
