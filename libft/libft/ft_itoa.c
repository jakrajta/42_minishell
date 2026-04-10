/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 20:07:05 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/16 19:05:28 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numerals(int n)
{
	int		count;
	long	nb;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		count++;
	}
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static void	fill_number(char *temp_n, long nb)
{
	while (nb > 0)
	{
		*(--temp_n) = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str_n;
	char	*temp;
	int		numerals;
	long	nb;

	nb = n;
	numerals = count_numerals(n);
	str_n = malloc(sizeof(char) * (numerals + 1));
	if (!str_n)
		return (NULL);
	temp = str_n + numerals;
	*temp = '\0';
	if (n == 0)
		*(--temp) = '0';
	if (nb < 0)
	{
		*str_n = '-';
		nb = -nb;
	}
	fill_number(temp, nb);
	return (str_n);
}
