#include "minishell.h"

static int	handle_redir(t_redir *redir)
{
	int	fd;
	int	std_fd;

	if (redir->tok_type == HEREDOC)
	{
		fd = redir->heredoc_fd;
		std_fd = STDIN_FILENO;
	}
	else if (redir->tok_type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		std_fd = STDIN_FILENO;
	}
	else
	{
		if (redir->tok_type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->tok_type == APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			return (0);
		std_fd = STDOUT_FILENO;
	}
	if (fd < 0)
		return (sys_error(NULL, redir->file, strerror(errno)));
	dup2(fd, std_fd);
	close(fd);
	return (0);
}

int	execute_redir(t_redir *redir)
{
	t_redir	*current;

	if (!redir)
		return (0);
	current = redir;
	while (current)
	{
		if (handle_redir(current))
			return (1);
		current = current->next;
	}
	return (0);
}
