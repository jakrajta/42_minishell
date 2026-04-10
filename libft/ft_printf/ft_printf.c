/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:13:55 by jakrajic          #+#    #+#             */
/*   Updated: 2025/09/18 17:55:58 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_typ(const char *__format, va_list args)
{
	int		count;
	char	specifier;

	specifier = *__format;
	count = 0;
	if (specifier == 'c')
		count = count + print_char(va_arg(args, int));
	else if (specifier == 's')
		count = count + print_str(va_arg(args, char *));
	else if (specifier == 'p')
		count = count + print_ptr(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		count = count + print_digits(va_arg(args, int));
	else if (specifier == 'u')
		count = count + print_udigits(va_arg(args, unsigned int));
	else if (specifier == 'x')
		count = count + print_hex_lower(va_arg(args, unsigned int));
	else if (specifier == 'X')
		count = count + print_hex_upper(va_arg(args, unsigned int));
	else if (specifier == '%')
		count = count + print_percent();
	else
		count = count + write(1, &specifier, 1);
	return (count);
}

int	ft_printf(const char *__format, ...)
{
	va_list	args;
	int		count;

	va_start(args, __format);
	count = 0;
	while (*__format != '\0')
	{
		if (*__format == '%' && *(__format + 1) != '\0')
		{
			__format++;
			count = count + handle_typ(__format, args);
		}
		else
		{
			count = count + write(1, __format, 1);
		}
		__format++;
	}
	va_end(args);
	return (count);
}
