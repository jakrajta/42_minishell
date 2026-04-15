#include "minishell.h"

/**
 * @brief Synchronizes the PWD and OLDPWD internal variables and environment.
 * * This helper function retrieves the current working directory using getcwd(),
 * updates the shell's internal tracking of 'pwd' and 'old_pwd', and reflects 
 * these changes in the exported environment variables. It ensures that 
 * commands like 'pwd' or 'env' always show the correct location after a 'cd'.
 * * @param env Pointer to the environment structure containing pwd and old_pwd.
 */
static void	update_pwd_var(t_env *env)
{
	char	*new_cwd;

	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
	{
		sys_error("pwd", NULL, strerror(errno));
		return ;
	}
	if (env->old_pwd)
		free(env->old_pwd);
	env->old_pwd = env->pwd;
	env->pwd = new_cwd;
	update_env_value("OLDPWD", env->old_pwd, env);
	update_env_value("PWD", env->pwd, env);
}

/**
 * @brief Executes the 'cd' (change directory) built-in command.
 * * Handles directory changes with the following logic:
 * - 'cd' without arguments: Changes to the directory specified in the HOME variable.
 * - 'cd -': Changes to the previous working directory (OLDPWD) and prints it.
 * - 'cd [path]': Changes to the specified relative or absolute path.
 * * If the transition is successful via chdir(), it triggers an update of the 
 * PWD and OLDPWD environment variables.
 * * @param cmd Pointer to the command structure containing the tokens/path.
 * @param shell Pointer to the shell structure for environment access.
 * @return 0 on success, or 1 if an error occurs (e.g., directory not found).
 */
int	execute_cd(t_cmd *cmd, t_shell *shell)
{
	char	*dir;

	if (!cmd || !cmd->tokens[0])
		return (1);
	if (!cmd->tokens[1])
	{
		dir = get_env_value("HOME", shell->env->env_copy);
		if (!dir)
			return (sys_error(cmd->tokens[0], NULL, "HOME not set"));
	}
	else if (ft_strncmp(cmd->tokens[1], "-", 2) == 0)
	{
		dir = get_env_value("OLDPWD", shell->env->env_copy);
		if (!dir)
			return (sys_error(cmd->tokens[0], NULL, "OLDPWD not set"));
		printf("%s\n", dir);
	}
	else
		dir = cmd->tokens[1];
	if (chdir(dir) != 0)
		return (sys_error(cmd->tokens[0], dir, strerror(errno)));
	update_pwd_var(shell->env);
	return (0);
}
