/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:44:35 by jakrajic          #+#    #+#             */
/*   Updated: 2026/04/22 15:24:45 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	allocate_buffer(char **buffer_storage, char **buffer)
{
	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*buffer == NULL)
		return (0);
	if (*buffer_storage == NULL)
	{
		*buffer_storage = ft_strdup("");
		if (*buffer_storage == NULL)
		{
			free(*buffer);
			return (0);
		}
	}
	return (1);
}

static char	*fill_buffer_storage(int fd, char **buffer_storage, char **buffer)
{
	ssize_t	bytes_read;
	char	*storage_temp;

	bytes_read = 1;
	while (!gnlft_strchr(*buffer_storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*buffer_storage);
			return ((*buffer_storage = NULL), NULL);
		}
		if (bytes_read == 0)
			break ;
		(*buffer)[bytes_read] = '\0';
		storage_temp = gnlft_strjoin(*buffer_storage, *buffer);
		if (storage_temp == NULL)
		{
			free(*buffer_storage);
			return ((*buffer_storage = NULL), NULL);
		}
		free(*buffer_storage);
		*buffer_storage = storage_temp;
	}
	return (*buffer_storage);
}

static char	*extract_line(char **buffer_storage)
{
	char	*buffer_storage_n_position;
	char	*line;
	char	*part_after_n;

	if (*buffer_storage == NULL)
		return (NULL);
	buffer_storage_n_position = gnlft_strchr(*buffer_storage, '\n');
	if (buffer_storage_n_position != NULL)
	{
		line = gnlft_substr(*buffer_storage, 0, (buffer_storage_n_position
					- *buffer_storage + 1));
		part_after_n = gnlft_strdup(buffer_storage_n_position + 1);
		free(*buffer_storage);
		*buffer_storage = part_after_n;
	}
	else
	{
		line = gnlft_strdup(*buffer_storage);
		free(*buffer_storage);
		*buffer_storage = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*buffer_storage;
	char		*line;
	int			result_ft;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result_ft = allocate_buffer(&buffer_storage, &buffer);
	if (result_ft == 0)
		return (NULL);
	buffer_storage = fill_buffer_storage(fd, &buffer_storage, &buffer);
	if (buffer_storage == NULL)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	if (buffer_storage == NULL || *buffer_storage == '\0')
	{
		free(buffer_storage);
		buffer_storage = NULL;
		return (NULL);
	}
	line = extract_line(&buffer_storage);
	return (line);
}
