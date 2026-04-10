/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:48:06 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 12:18:57 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function f to each character
 *  of the string s to create a new string
 * resulting from successive applications of f.
 * @param s The input string.
 * @param f The function to apply to each character.
 *  It receives the index of the character
 * and the character itself, and returns the transformed character.
 * @return A newly allocated string resulting 
 * from the successive applications of f.
 * Returns NULL if allocation fails or if s or f is NULL.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	char			*temp_dest;
	char const		*temp_s;
	unsigned int	len_s;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (len_s + 1));
	if (dest == NULL)
		return (NULL);
	temp_s = s;
	temp_dest = dest;
	i = 0;
	while (*temp_s)
	{
		*temp_dest = f(i, *temp_s);
		temp_s++;
		temp_dest++;
		i++;
	}
	*temp_dest = '\0';
	return (dest);
}
