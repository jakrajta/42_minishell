/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:02:17 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/17 12:18:30 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function f to each character 
 * of the string passed as argument,
 * passing its index as first argument. Each character is passed by address
 * to f to be modified if necessary.
 * @param s The string to iterate over.
 * @param f The function to apply to 
 * each character. It receives the index of the character
 * and a pointer to the character itself.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char			*temp_s;
	unsigned int	i;

	if (!s || !f)
		return ;
	temp_s = s;
	i = 0;
	while (*temp_s)
	{
		f(i, temp_s);
		temp_s++;
		i++;
	}
}
