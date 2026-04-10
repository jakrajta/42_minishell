#include "minishell.h"

/**
 * @brief Removes quotes from a string in-place.
 * * This function traverses the string and removes the outermost layers 
 * of single or double quotes while preserving the characters inside them. 
 * It uses a source and destination pointer to shift characters and 
 * effectively overwrite the quotes without additional memory allocation.
 * * @param str The string to be processed. The modification is done directly 
 * on this pointer.
 * @return void
 */
void	remove_quotes(char *str)
{
	char	*dest;
	char	*src;
	char	in_quote;

	dest = str;
	src = str;
	in_quote = 0;
	while (*src)
	{
		if ((*src == '\"' || *src == '\'') && in_quote == 0)
			in_quote = *src;
		else if (*src == in_quote)
			in_quote = 0;
		else
			*dest++ = *src;
		src++;
	}
	*dest = '\0';
}
