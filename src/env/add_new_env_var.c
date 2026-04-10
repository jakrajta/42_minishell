#include "minishell.h"

/**
 * @brief Expands the environment array to include a new variable.
 * * 1. Calculates the current size of the environment.
 * 2. Allocates a new array with space for the existing variables, 
 * the new one, and a NULL terminator (len + 2).
 * 3. Transfers existing pointers to the new array
 *  without re-duplicating strings.
 * 4. Appends the new variable using ft_strdup.
 * 5. Frees the old pointer array (but not the strings it contained).
 * * @param env The current NULL-terminated environment array.
 * @param new_var The "NAME=VALUE" string to be added.
 * @return A pointer to the new environment array, or NULL on allocation failure.
 */
char	**add_new_env_var(char **env, char *new_var)
{
	int		len;
	char	**new_env;
	char	**env_temp;
	char	**env_to_free;

	len = tokens_count(env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	env_temp = new_env;
	env_to_free = env;
	while (env && *env)
		*env_temp++ = *env++;
	*env_temp = ft_strdup(new_var);
	*(env_temp + 1) = NULL;
	free(env_to_free);
	return (new_env);
}
