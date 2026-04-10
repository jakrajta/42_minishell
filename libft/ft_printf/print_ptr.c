/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:16:59 by jakrajic          #+#    #+#             */
/*   Updated: 2025/09/18 17:57:08 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_hex_lower_long(unsigned long nbr)
{
	int		count;
	char	*dec_digits;

	dec_digits = "0123456789abcdef";
	count = 0;
	if (nbr >= 16)
		count = count + print_hex_lower_long(nbr / 16);
	count = count + print_char(*(dec_digits + (nbr % 16)));
	return (count);
}

int	print_ptr(void *ptr)
{
	uintptr_t	address;
	int			count;

	if (ptr == NULL)
		return (print_str("(nil)"));
	address = (uintptr_t)ptr;
	count = 0;
	count += print_str("0x");
	count += print_hex_lower_long((unsigned long)address);
	return (count);
}
