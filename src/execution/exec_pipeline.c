#include "minishell.h"

/**
 * @brief Handles the setup of a single pipeline stage (pipe and fork).
 *
 * This function performs the necessary steps for one command in the pipeline:
 * 1. Creates a pipe if there is a subsequent command.
 * 2. Forks the process.
 * 3. In the child, executes the command.
 * 4. In the parent, updates the pipeline state (prev_fd and last_pid).
 *
 * @param current Pointer to the current command node.
 * @param shell Pointer to the main shell structure containing pipeline state.
 */
static void	run_pipeline_step(t_cmd *current, t_shell *shell)
{
	int	pipe_fds[2];

	if (current->next && pipe(pipe_fds) == -1)
	{
		sys_error("pipe", NULL, strerror(errno));
		return ;
	}
	shell->last_pid = fork();
	if (shell->last_pid == -1)
	{
		sys_error("fork", NULL, strerror(errno));
		return ;
	}
	if (shell->last_pid == 0)
		child_process(pipe_fds, current, shell);
	parent_process(&shell->prev_fd, pipe_fds, current);
}

/**
 * @brief Orchestrates the execution of a pipeline of commands.
 *
 * Iterates through the command linked list, setting up the pipeline state
 * and launching each command in a child process. After starting all commands,
 * it waits for their completion and restores signal handling.
 *
 * @param shell Pointer to the main shell structure.
 * @return Returns 0 upon successful pipeline execution.
 */
int	execute_pipeline(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmd;
	shell->prev_fd = -1;
	shell->last_pid = -1;
	parent_signal_setup();
	while (current)
	{
		run_pipeline_step(current, shell);
		current = current->next;
	}
	wait_for_all_children(shell);
	signal_setup();
	return (0);
}
