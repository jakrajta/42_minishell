#include "minishell.h"

int execute_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->tokens || !cmd->tokens[0])
		 return (1);

	if (cmd->builtin == ECHO)
		return (execute_echo(cmd));
	if (cmd->builtin == PWD)
		return (execute_pwd(shell->env));
	if (cmd->builtin == CD)
		return (execute_cd(cmd, shell));
	if (cmd->builtin == EXIT)
		return (execute_exit(cmd, shell));
	if (cmd->builtin == ENV)
		return (execute_env(cmd, shell));
	if (cmd->builtin == EXPORT)
		return (execute_export(cmd, shell));
	if (cmd->builtin == UNSET)
		return (execute_unset(cmd, shell));
	return (0);
}