#include "minishell.h"

/**
 * @brief Creates a deep copy of the environment variables array.
 * * 1. Counts the number of environment variables to allocate the pointer array.
 * 2. Duplicates each string using ft_strdup to ensure 
 * the copy has its own memory.
 * 3. Provides a rollback mechanism: if a single allocation fails, it frees all 
 * previously allocated strings and the array itself to prevent memory leaks.
 * * @param envp The NULL-terminated array of system environment variables.
 * @return A newly allocated NULL-terminated copy of the environment, 
 * or NULL on failure.
 */
char	**copy_env(char **envp)
{
	char	**copy;
	char	**start;

	if (!envp)
		return (NULL);
	copy = malloc(sizeof(char *) * (tokens_count(envp) + 1));
	if (!copy)
		return (NULL);
	start = copy;
	while (*envp)
	{
		*copy = ft_strdup(*envp);
		if (!*copy)
		{
			while (copy > start)
				free(*--copy);
			return (free(start), NULL);
		}
		copy++;
		envp++;
	}
	*copy = NULL;
	return (start);
}
