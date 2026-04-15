#include "minishell.h"

void	execute_commands(t_shell *shell)
{
	int	stdout_backup;
	int	stdin_backup;

	if (shell->cmd->skip_exec)
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (!shell || !shell->cmd)
		return ;
	if (execute_heredoc(shell->cmd) != 0)
	{
		shell->last_exit_status = 130;
		return (close_heredoc_fd(shell->cmd));
	}
	if (shell->cmd->builtin != B_NONE && !shell->cmd->next)
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		if (execute_redir(shell->cmd->redir) == 0)
			shell->last_exit_status = execute_builtin(shell->cmd, shell);
		else
			shell->last_exit_status = 1;
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
	}
	else
		execute_pipeline(shell);
	close_heredoc_fd(shell->cmd);
}
