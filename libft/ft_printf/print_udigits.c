/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_udigits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:14:47 by jakrajic          #+#    #+#             */
/*   Updated: 2025/09/18 17:57:51 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_udigits(unsigned int n)
{
	int		count;
	char	digit;

	count = 0;
	if (n >= 10)
		count = count + print_udigits(n / 10);
	digit = (n % 10) + '0';
	count = count + print_char(digit);
	return (count);
}
