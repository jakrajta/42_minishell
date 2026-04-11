#include "minishell.h"

void	execute_commands(t_shell *shell)
{
	int stdout_backup;
	int stdin_backup;
	
	if (shell->cmd->skip_exec)
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (!shell || !shell->cmd)
		return ;
	if (execute_heredoc(shell->cmd) != 0)  //zde se ctou vsechny heredocky v cmd_line
	// shell se zastavi a ceka az uzivatel vypise ceschny heredocy vsechny se vypisuji najednou)
	// tyto data se pak ulozi do pipe a jejich fd[0] se ulozi do struktury 
	{
		shell->last_exit_status = 130;
		return (close_heredoc_fd(shell->cmd));
	}
	if (shell->cmd->builtin != NONE && !shell->cmd->next)
	{
		stdin_backup = dup(STDIN_FILENO);  //zalohuju vystup a vstup na terminal pro rediry s cmd
		stdout_backup = dup(STDOUT_FILENO);
		if (execute_redir(shell->cmd->redir) == 0)  // fce se vykona spravne i kdyz tam neni zadny redir
			// v pripade v redir je heredoc tak handle redir da heredoc fd[0] a dup2  napoji ho na vstup
			shell->last_exit_status = execute_builtin_cmd(shell->cmd, shell);  // oiku neni pipe
		else
			shell->last_exit_status = 1;
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
	}
	else
		execute_pipeline(shell); //heredocy priravene nahore se tady v child exekuuji
	close_heredoc_fd(shell->cmd);
}
