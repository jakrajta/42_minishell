#include "minishell.h"

/**
 * @brief Finds the index of an environment variable by its name.
 *
 * Calculates the name length (up to '=') and iterates through the env array.
 * A match is confirmed only if the string matches exactly and is followed 
 * by a '=' or a null terminator to prevent prefix-only matches.
 *
 * @param env The environment array to search.
 * @param name The name to search for (can be "NAME" or "NAME=value").
 * @return int The index of the variable if found, -1 otherwise.
 */
int	is_env_name(char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
