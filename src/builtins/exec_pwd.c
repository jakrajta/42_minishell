#include "minishell.h"

/** @brief fce receives current working directory by getcwd and
 * displays it to terminal
 * parent fce: execute_builtin_cmd();
*/
int	execute_pwd(t_env *env)
{
	char	*cwd;

	cwd = get_env_value("PWD", env->env_copy);
	if (cwd)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	else
		return (sys_error("pwd", NULL, "error retreiving current directory"));
}
