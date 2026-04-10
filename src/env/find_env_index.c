#include "minishell.h"

/**
 * @brief Finds the index of an environment variable by its name.
 *
 * Calculates the length of the name (until '=') and searches the env array.
 * A match is only confirmed if the lengths are identical and the character 
 * following the match in the environment is either '=' or '\0'.
 *
 * @param env The environment array to search in.
 * @param name The name of the variable to find (can be "VAR" or "VAR=val").
 * @return int The index of the variable if found, -1 otherwise.
 */
int	find_env_index(char **env, char *name)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (name[len] && name[len] != '=')
		len++;
	while (env[index])
	{
		if (ft_strncmp(env[index], name, len) == 0 && (env[index][len] == '='
			|| env[index][len] == '\0'))
			return (index);
		index++;
	}
	return (-1);
}
