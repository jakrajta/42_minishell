#include "minishell.h"

/**
 * @brief Initializes the environment env structure.
 * * * 1. Allocates memory for the t_env structure.
 * * 2. Creates a deep copy of the system environment variables.
 * * 3. Sets PWD: If found in env, it duplicates it; otherwise, it fetches 
 * * the current working directory from the system.
 * * 4. Sets PATH: If found, it splits it into a null-terminated array 
 * * of strings for easy command searching.
 * * @param envp The raw environment pointer from the system.
 * @return A pointer to the initialized t_env structure, or NULL on failure.
 */
t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*path_from_system;
	char	*pwd_temp;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env_copy = copy_env(envp);
	if (!env->env_copy)
		return (free(env), NULL);
	env->split_paths = NULL;
	pwd_temp = get_env_value("PWD", env->env_copy);
	if (pwd_temp)
		env->pwd = ft_strdup(pwd_temp);
	else
		env->pwd = getcwd(NULL, 0);
	env->old_pwd = NULL;
	path_from_system = get_env_value("PATH", env->env_copy);
	if (path_from_system != NULL)
	{
		env->split_paths = general_split(path_from_system, ":");
		if (!env->split_paths)
			return (free_env(&env), NULL);
	}
	return (env);
}
