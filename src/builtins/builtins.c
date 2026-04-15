#include "minishell.h"

/**
 * @brief Identifies the type of a builtin command.
 *
 * Compares the given command string against a list of supported builtins:
 * pwd, exit, echo, cd, env, export, and unset.
 *
 * @param cmd The command string to identify.
 * @return t_builtin The corresponding enum value (PWD, EXIT, etc.), 
 * or NONE if the command is not a builtin.
 */
t_builtin	get_builtin_type(char *cmd)
{
	if (!cmd)
		return (B_NONE);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (B_PWD);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (B_EXIT);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (B_ECHO);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (B_CD);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (B_ENV);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (B_EXPORT);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (B_UNSET);
	return (B_NONE);
}
