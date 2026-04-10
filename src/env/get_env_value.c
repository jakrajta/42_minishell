#include "minishell.h"

/**
 * @brief Retrieves the value of a specific environment variable.
 * * This function searches the environment array for a variable matching 
 * the given name. It ensures an exact match by checking if the character 
 * immediately following the name in the environment string is an '=' sign.
 * * @note This function returns a pointer to the value within the original 
 * environment array. It does not allocate new memory.
 * * @param name The name of the variable to search for.
 * @param env_copy The NULL-terminated array of environment strings.
 * @return A pointer to the start of the value string, or NULL if not found.
 */
char	*get_env_value(char *name, char **env_copy)
{
	int		i;
	int		len;
	char	*env_value;

	if (!name || !env_copy)
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (env_copy[i])
	{
		if (ft_strncmp(env_copy[i], name, len) == 0 && env_copy[i][len] == '=')
		{
			env_value = (env_copy[i] + (len + 1));
			return (env_value);
		}
		i++;
	}
	return (NULL);
}
