#include "minishell.h"

/**
 * @brief Executes the env builtin command.
 *
 * Prints all environment variables that have an assigned value (containing '=').
 * If any arguments are provided, it mimics the behavior of a simple shell by 
 * returning an error, as this implementation only handles 'env' without options.
 *
 * @param cmd Pointer to the command structure.
 * @param shell Pointer to the shell structure containing the environment.
 * @return int 0 on success, 1 on environment error, 
 * or error code from sys_error.
 */
int	execute_env(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!shell->env || !shell->env->env_copy)
		return (1);
	if (cmd->tokens_count > 1)
		return (sys_error(cmd->tokens[0], NULL, "No such file or directory"));
	i = 0;
	while (shell->env->env_copy[i])
	{
		if (ft_strchr(shell->env->env_copy[i], '='))
		{
			ft_putstr_fd(shell->env->env_copy[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}
