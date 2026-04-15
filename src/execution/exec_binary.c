#include "minishell.h"

static int	path_error(char *cmd_token)
{
	int	exit_status;

	if (ft_strchr(cmd_token, '/'))
	{
		if (is_dir(cmd_token))
		{
			sys_error(cmd_token, NULL, "Is directory");
			exit_status = 126;
		}
		else
		{
			sys_error(cmd_token, NULL, "No such file or directory");
			exit_status = 127;
		}
	}
	else
	{
		sys_error(cmd_token, NULL, "command not found");
		exit_status = 127;
	}
	return (exit_status);
}

int	execute_binary(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int		exit_status;

	path = get_cmd_path(shell, cmd->tokens[0]);
	if (!path)
	{
		exit_status = path_error(cmd->tokens[0]);
		free_shell(&shell);
		exit(exit_status);
	}
	if (isatty(STDIN_FILENO))
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_term);
	if (execve(path, cmd->tokens, shell->env->env_copy) == -1)
	{
		sys_error(cmd->tokens[0], NULL, strerror(errno));
		free(path);
		free_shell(&shell);
		exit(126);
	}
	return (0);
}
