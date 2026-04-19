#include "minishell.h"

/**
 * @brief Manages file descriptors in the parent process during pipeline execution.
 *
 * Closes the input pipe of the previous command and updates the state to 
 * store the current read-end pipe for the next command. This ensures 
 * efficient file descriptor management and prevents pipe leaks.
 *
 * @param prev_fd Pointer to the file descriptor of the previous pipe input.
 * @param pipe_fds Array containing the current pipe's file descriptors.
 * @param current Pointer to the current command node.
 */
void	parent_process(int *prev_fd, int pipe_fds[2], t_cmd *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(pipe_fds[1]);
		*prev_fd = pipe_fds[0];
	}
}
/**
 * @brief Updates the shell's exit status based on the process that terminated.
 *
 * Compares the terminated process PID with the shell's last recorded PID.
 * If they match, it updates the shell's exit status. Handles both normal
 * termination and termination by signals (SIGINT, SIGQUIT).
 *
 * @param shell Pointer to the main shell structure.
 * @param status The exit status of the terminated process (from wait()).
 * @param pid The PID of the process that just terminated.
 */
static void update_exit_status(t_shell * shell, int status, pid_t pid)
{
	if (pid != shell->last_pid)
		return ;
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_exit_status = 128 + WTERMSIG(status);
		if (shell->last_exit_status == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (shell->last_exit_status == 130)
			ft_putstr_fd ("\n", 2);
	}
}

/**
 * @brief Waits for all child processes to complete.
 *
 * Continuously calls wait() to collect all child processes. For each 
 * process, it checks if it was the last command in the pipeline and 
 * updates the shell's exit status accordingly. Re-enables terminal 
 * control characters upon completion.
 *
 * @param shell Pointer to the main shell structure.
 */
void	wait_for_all_children(t_shell *shell)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		update_exit_status(shell, status, pid);
		pid = wait(&status);
	}
	toggle_echoctl(0);
}
