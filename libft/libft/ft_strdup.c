/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:59:37 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/12 17:00:27 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	const char	*temp_str;
	char		*str2;
	size_t		len;
	char		*str2_start;

	temp_str = str;
	len = ft_strlen(str);
	str2 = (char *)malloc(len + 1);
	if (str2 == NULL)
		return (NULL);
	str2_start = str2;
	while (*temp_str != '\0')
	{
		*str2 = *temp_str;
		temp_str++;
		str2++;
	}
	*str2 = '\0';
	return (str2_start);
}
