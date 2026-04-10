/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:11:01 by jakrajic          #+#    #+#             */
/*   Updated: 2025/09/18 17:56:32 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex_lower(unsigned int n)
{
	int		count;
	char	*dec_digits;

	dec_digits = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count = count + print_hex_lower(n / 16);
	count = count + print_char(*(dec_digits + (n % 16)));
	return (count);
}
