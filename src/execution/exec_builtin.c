#include "minishell.h"

/**
 * @brief Dispatcher function that identifies and executes shell built-in commands.
 * * This function acts as a central hub for built-in execution. It checks the 
 * command's builtin type (assigned during parsing) and calls the corresponding 
 * handler function. It ensures that standard shell utilities like echo, cd, 
 * or export are executed within the shell's logic rather than as external binaries.
 * * @param cmd Pointer to the command structure containing arguments and builtin type.
 * @param shell Pointer to the shell structure for accessing environment and state.
 * @return The exit status returned by the specific built-in function, 
 * 1 if the command is invalid, or 0 if no matching builtin is found.
 */
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->tokens || !cmd->tokens[0])
		return (1);
	if (cmd->builtin == B_ECHO)
		return (execute_echo(cmd));
	if (cmd->builtin == B_PWD)
		return (execute_pwd(shell->env));
	if (cmd->builtin == B_CD)
		return (execute_cd(cmd, shell));
	if (cmd->builtin == B_EXIT)
		return (execute_exit(cmd, shell));
	if (cmd->builtin == B_ENV)
		return (execute_env(cmd, shell));
	if (cmd->builtin == B_EXPORT)
		return (execute_export(cmd, shell));
	if (cmd->builtin == B_UNSET)
		return (execute_unset(cmd, shell));
	return (0);
}
