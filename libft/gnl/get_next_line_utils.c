/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:46:06 by jakrajic          #+#    #+#             */
/*   Updated: 2025/10/02 16:47:39 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnlft_strchr(const char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	gnlft_strlen(const char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

char	*gnlft_strdup(const char *str)
{
	char	*str_copy;
	char	*str_copy_start;

	if (str == NULL)
		return (NULL);
	str_copy = malloc(ft_strlen(str) + 1);
	if (str_copy == NULL)
		return (NULL);
	str_copy_start = str_copy;
	while (*str != '\0')
		*str_copy++ = *str++;
	*str_copy = '\0';
	return (str_copy_start);
}

char	*gnlft_strjoin(const char *str1, const char *str2)
{
	char	*dest;
	char	*temp_dest;

	if (str1 == NULL)
		str1 = "";
	if (str2 == NULL)
		str2 = "";
	dest = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (dest == NULL)
		return (NULL);
	temp_dest = dest;
	while (*str1)
		*temp_dest++ = *str1++;
	while (*str2)
		*temp_dest++ = *str2++;
	*temp_dest = '\0';
	return (dest);
}

char	*gnlft_substr(const char *str, unsigned int start, size_t len)
{
	char	*substr;
	char	*substr_temp;
	size_t	real_len;

	if (str == NULL)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	if ((start + len) > ft_strlen(str))
		real_len = ft_strlen(str) - start;
	else
		real_len = len;
	substr = malloc((real_len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	substr_temp = substr;
	while (real_len-- > 0)
	{
		*substr_temp++ = *(str + start);
		start++;
	}
	*substr_temp = '\0';
	return (substr);
}
