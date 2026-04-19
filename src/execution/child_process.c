#include "minishell.h"

/**
 * @brief Performs file descriptor redirection for the child process.
 *
 * Configures the standard input and output of the child process. It sets up 
 * the input from the previous pipe (if applicable) and the output to the 
 * current pipe (if there is a next command).
 *
 * @param current Pointer to the current command node.
 * @param prev_fd File descriptor of the input pipe from the previous command.
 * @param pipe_fds Array containing the current pipe's file descriptors.
 */
static void	child_redirect(t_cmd *current, int prev_fd, int pipe_fds[2])
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(1);
		close(prev_fd);
	}
	if (current->next)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			exit (1);
		close(pipe_fds[1]);
	}
}

/**
 * @brief Executes the command within a child process.
 *
 * Prepares the child environment by setting up signals, performing I/O 
 * redirection, and handling both built-in commands and external binaries. 
 * If a command fails or is empty, it cleans up shell resources and exits.
 *
 * @param pipe_fds Array containing the current pipe's file descriptors.
 * @param current Pointer to the current command node.
 * @param shell Pointer to the main shell structure.
 */
void	child_process(int pipe_fds[2], t_cmd *current, t_shell *shell)
{
	int	exit_status;

	child_signal_setup();
	child_redirect(current, shell->prev_fd, pipe_fds);
	if (current->redir)
	{
		if (execute_redir(current->redir))
		{
			free_shell(&shell);
			exit(1);
		}
	}
	if (!current->tokens || !current->tokens[0])
	{
		free_shell(&shell);
		exit(0);
	}
	if (current->builtin != B_NONE)
	{
		exit_status = execute_builtin(current, shell);
		free_shell(&shell);
		exit(exit_status);
	}
	execute_binary(current, shell);
	exit(0);
}
