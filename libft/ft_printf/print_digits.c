/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:47:38 by jakrajic          #+#    #+#             */
/*   Updated: 2025/09/18 17:56:23 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_digits(int n)
{
	int		count;
	long	nb;
	char	digit;

	count = 0;
	nb = (long)n;
	if (nb < 0)
	{
		count = count + print_char('-');
		nb = -nb;
	}
	if (nb >= 10)
		count = count + print_digits(nb / 10);
	digit = (nb % 10) + '0';
	count = count + print_char(digit);
	return (count);
}
