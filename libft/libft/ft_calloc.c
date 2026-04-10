/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:53:49 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/16 17:48:12 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	void	*str;
	size_t	total_bytes;

	if (count == 0 && n == 0)
	{
		count = 1;
		n = 1;
	}
	if (n != 0 && count > ((size_t)-1) / n)
		return (NULL);
	total_bytes = count * n;
	str = malloc(total_bytes);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, total_bytes);
	return (str);
}
