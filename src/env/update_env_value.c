#include "minishell.h"

/**
 * @internal
 * @brief Helper function to construct a "NAME=VALUE" string.
 * * @param var_name Variable name.
 * @param value Variable value.
 * @return An allocated string, or NULL on failure.
 */
static char	*create_env_var(char *var_name, char *value)
{
	char	*new_var;

	new_var = triple_strjoin(var_name, "=", value);
	if (!new_var)
		return (NULL);
	return (new_var);
}

/**
 * @brief Updates an existing environment variable or adds a new one.
 * * 1. Creates a new "NAME=VALUE" string using create_env_var.
 * 2. Searches the current environment for an exact match of the variable name.
 * 3. If found: Frees the old string and replaces it with the new one.
 * 4. If not found: Appends the new variable to the environment array 
 * using add_new_env_var.
 * * @param var_name The name of the variable (e.g., "PATH").
 * @param value The value to be assigned to the variable.
 * @param env Pointer to the environment structure.
 */
void	update_env_value(char *var_name, char *value, t_env *env)
{
	int		name_len;
	char	*new_var;
	int		i;
	char	**env_temp;

	name_len = ft_strlen(var_name);
	new_var = create_env_var(var_name, value);
	if (!new_var)
		return ;
	i = 0;
	while (env->env_copy && env->env_copy[i])
	{
		if (ft_strncmp(env->env_copy[i], var_name, name_len) == 0
			&& env->env_copy[i][name_len] == '=')
		{
			free(env->env_copy[i]);
			env->env_copy[i] = new_var;
			return ;
		}
		i++;
	}
	env_temp = add_new_env_var(env->env_copy, new_var);
	if (env_temp)
		env->env_copy = env_temp;
	free(new_var);
}
