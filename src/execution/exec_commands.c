#include "minishell.h"

/**
 * @brief Executes a built-in command within the main shell process.
 *
 * Backs up the standard input and output file descriptors, performs 
 * redirections, executes the built-in command, and restores the original 
 * I/O streams. This ensures the main shell process remains unaffected 
 * by the redirection.
 *
 * @param shell Pointer to the main shell structure containing command data.
 */
static void	execute_single_builtin(t_shell *shell)
{
	int	stdout_backup;
	int	stdin_backup;

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

/**
 * @brief Orchestrates the execution of commands.
 *
 * The primary manager for command execution. It handles:
 * 1. Checks if execution should be skipped.
 * 2. Prepares heredoc documents.
 * 3. Decides whether to run a built-in command in the main process 
 * or initiate a pipeline for external commands.
 * 4. Ensures proper cleanup of resources after execution.
 *
 * @param shell Pointer to the main shell structure.
 */
void	execute_commands(t_shell *shell)
{
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
		execute_single_builtin(shell);
	else
		execute_pipeline(shell);
	close_heredoc_fd(shell->cmd);
}
