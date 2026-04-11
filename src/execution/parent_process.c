#include "minishell.h"

void parent_process(int *prev_fd, int pipe_fds[2], t_cmd *current)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		//*prev_fd = -1; 
	}	
	if (current->next)
	{
		close(pipe_fds[1]);  //prikaz na druhe strane pipe cte data v cyklech 
		// a dostane se do EOF jedine, pokud ji rodic zavre. pokud by nezavrel bude cekat na dalsi data
		*prev_fd =  pipe_fds[0];
	}
	// else 
	// 	*prev_fd = -1;  // v pristim kole nebude viset stare fd
}

void	wait_for_all_children(t_shell *shell, pid_t last_pid)
{
	int	status;
	pid_t	pid;
	status = 0;
	while ((pid = wait(&status)) > 0)  // ceka na libovolne dite a ulozi jeho stav  do status
	{
		if (pid == last_pid) // posledni clanek v pipeline
		{
			if (WIFEXITED(status))// vraci true pokud proces skoncil ok (volanim exit nebo navratem z main)
				shell->last_exit_status = WEXITSTATUS(status); //vrati cislo, ktere posal exit
			else if (WIFSIGNALED(status))  //  vraci true pokud proces skoncil signalem
			{
				shell->last_exit_status = 128 + WTERMSIG(status);  // 128 zabiti signalem + druh
				if (shell->last_exit_status == 131)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				else if (shell->last_exit_status == 130)
					ft_putstr_fd ("\n", 2);
			}
		}
	}
}
