#include "minishell.h"

static int	prepare_heredoc(char *delimiter)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (sys_error("pipe", NULL, strerror(errno)));
	while (1)
	{
		line = readline("> ");
		if (!line || g_status == 130)
		{
			if (!line && g_status != 130)
				display_warning(delimiter);
			break;
		}
		if (my_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}

int	execute_heredoc(t_cmd *cmd)
{
	t_cmd	*cmd_cur;
	t_redir	*redir_cur;

	heredoc_signal_setup();
	cmd_cur = cmd;
	while (cmd_cur)
	{
		redir_cur = cmd_cur->redir;
		while (redir_cur)
		{
			if (redir_cur->tok_type == HEREDOC)
			{
				redir_cur->heredoc_fd = prepare_heredoc(redir_cur->file);
				if (g_status == 130)
				{
					open("/dev/tty", O_RDONLY);
					return (signal_setup(), 1);
				}
			}
			redir_cur = redir_cur->next;
		}
		cmd_cur = cmd_cur->next;
	}
	signal_setup();
	return (0);
}

void	close_heredoc_fd(t_cmd *cmd)
{
	t_cmd	*cmd_cur;
	t_redir	*redir_cur;

	cmd_cur = cmd;
	while (cmd_cur)
	{
		redir_cur = cmd_cur->redir;
		while (redir_cur)
		{
			if (redir_cur->tok_type == HEREDOC && redir_cur->heredoc_fd != -1)
			{
				close(redir_cur->heredoc_fd);
				redir_cur->heredoc_fd = -1;
			}
			redir_cur = redir_cur->next;
		}
		cmd_cur = cmd_cur->next;
	}
}
