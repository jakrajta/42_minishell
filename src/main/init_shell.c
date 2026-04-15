#include "minishell.h"

/**
 * @brief Top-level initialization of the shell's main data structure.
 * * This function orchestrates the setup of the entire shell by:
 * 1. Allocating the master t_shell structure.
 * 2. Initializing the environment subsystem via init_env_struct.
 * 3. Setting default values for command lines, tokens, and exit status.
 * 4. Cleaning up OLDPWD to ensure a consistent state at startup.
 * * @param envp Raw environment array from the operating system.
 * @return A pointer to the fully initialized t_shell, or NULL if any step fails.
 */
t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = init_env(envp);
	if (!shell->env)
		return (free(shell), NULL);
	update_env_value("OLDPWD", "", shell->env);
	shell->cmd_line = NULL;
	shell->all_tokens = NULL;
	shell->cmd = NULL;
	shell->last_exit_status = 0;
	return (shell);
}
