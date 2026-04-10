/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:08:30 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/12 15:08:54 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr[11];
	char	*temp_nbr;
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	temp_nbr = nbr;
	while (nb > 0)
	{
		*temp_nbr++ = nb % 10 + '0';
		nb /= 10;
	}
	while (--temp_nbr >= nbr)
		write(fd, temp_nbr, 1);
}
