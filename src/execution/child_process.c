#include "minishell.h"

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

void	child_process(int prev_fd, int pipe_fds[2], t_cmd *current,
	t_shell *shell)
{
	int	exit_status;

	child_signal_setup();
	child_redirect(current, prev_fd, pipe_fds);
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
