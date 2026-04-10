#include "minishell.h"

/**
 * @brief Removes an environment variable at a specific index.
 *
 * Creates a new copy of the environment array, skipping the element at 
 * the given index. It frees the string at that index and the old array 
 * pointer itself to prevent memory leaks.
 *
 * @param env The current environment array (char **).
 * @param env_index The index of the variable to be removed.
 * @return char** Pointer to the new environment array, or NULL on failure.
 */
static char	**remove_env_var(char **env, int env_index)
{
	char	**new_env;
	char	**env_temp;
	char	**env_to_free;
	int		len;
	int		i;

	len = tokens_count(env);
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	env_temp = new_env;
	env_to_free = env;
	i = 0;
	while (*env && i < len)
	{
		if (i == env_index)
			free(*env);
		else
			*env_temp++ = *env;
		env++;
		i++;
	}
	*env_temp = NULL;
	free(env_to_free);
	return (new_env);
}

/**
 * @brief Implementation of the builtin unset command.
 *
 * Iterates through command arguments and checks if they are valid identifiers.
 * If a variable exists in the environment, it is removed using remove_env_var.
 *
 * @param cmd Structure containing command tokens (arguments).
 * @param shell Main shell structure holding the environment copy.
 * @return int Always returns 0.
 */
int	execute_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	env_index;

	i = 1;
	while (cmd->tokens[i] && !ft_strchr(cmd->tokens[i], '='))
	{
		if (is_env_name(cmd->tokens[i]))
		{
			env_index = find_env_index(shell->env->env_copy, cmd->tokens[i]);
			if (env_index >= 0)
				shell->env->env_copy = remove_env_var(shell->env->env_copy,
						env_index);
		}
		else
			sys_error("unset", cmd->tokens[i], "not a valid identifier");
		i++;
	}
	return (0);
}
