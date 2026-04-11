#include "minishell.h"

int  execute_pipeline(t_shell *shell)
{
	t_cmd	*current;
	int pipe_fds[2];  // 0 pro cteni, 1 pro zapis
	int prev_fd;  // se ulozim predchozi fd
	pid_t pid;

	current = shell->cmd; // node pro jeden prikaz
	prev_fd = -1;   //zatim zadne prev neexistuje,  fd nemuze byt zaporny, proto -1
	pid = -1;

	parent_signal_setup();
	while(current) // projizdim vsechny node, kde jsou ulozeny prikazy
	{
		if (current->next && pipe(pipe_fds) == -1)  //rodic udela pipu
		{
			sys_error("pipe", NULL, strerror(errno));
			break;
		}
		pid = fork();  // rodic forkne pro kazdy prikaz dite, aby vsechny prikazy mohly 
		if (pid == -1)
		{
			sys_error("fork", NULL, strerror(errno));
			break;
		}
		if (pid == 0) // dite
			child_process(prev_fd, pipe_fds, current, shell);
		parent_process(&prev_fd, pipe_fds, current);  // rodic musi po diteti uklidit,
		// kvuli forku ma take pristup pipe_fds -musi je zavrit a fd[0] ulozit do prev_ft,
		//  dite dalsiho prilazu ho bude potrebovat
		current = current->next;
	}
	wait_for_all_children(shell, pid);
	signal_setup();
	return (0);
}

