#include "minishell.h"

int	execute_pipeline(t_shell *shell)
{
	t_cmd	*current;
	int		pipe_fds[2];
	int		prev_fd;
	pid_t	pid;

	current = shell->cmd;
	prev_fd = -1;
	pid = -1;
	parent_signal_setup();
	while (current)
	{
		if (current->next && pipe(pipe_fds) == -1)
		{
			sys_error("pipe", NULL, strerror(errno));
			break ;
		}
		pid = fork();
		if (pid == -1)
		{
			sys_error("fork", NULL, strerror(errno));
			break ;
		}
		if (pid == 0)
			child_process(prev_fd, pipe_fds, current, shell);
		parent_process(&prev_fd, pipe_fds, current);
		current = current->next;
	}
	wait_for_all_children(shell, pid);
	signal_setup();
	return (0);
}
