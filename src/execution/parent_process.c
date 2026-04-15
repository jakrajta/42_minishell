#include "minishell.h"

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

void	wait_for_all_children(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
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
		pid = wait(&status);
	}
	toggle_echoctl(0);
}
