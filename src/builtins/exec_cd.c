#include "minishell.h"

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
