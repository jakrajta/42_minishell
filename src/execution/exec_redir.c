#include "minishell.h"

/**
 * @brief Determines the file descriptor for a specific redirection type.
 *
 * Checks the token type of the redirection and either retrieves the 
 * existing heredoc file descriptor or opens the target file with 
 * appropriate flags.
 *
 * @param redir Pointer to the current redirection node.
 * @return The file descriptor, -1 on error, or -2 if type is unknown.
 */
static int	get_redir_fd(t_redir *redir)
{
	int	fd;

	if (redir->tok_type == HEREDOC)
		fd = redir->heredoc_fd;
	else if (redir->tok_type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->tok_type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->tok_type == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -2;
	return (fd);
}

/**
 * @brief Handles the application of a single redirection.
 *
 * Determines the target standard stream (stdin/stdout), acquires the file
 * descriptor, and applies the redirection using dup2.
 *
 * @param redir Pointer to the current redirection node.
 * @return 0 on success, 1 on system error.
 */
static int	handle_redir(t_redir *redir)
{
	int	fd;
	int	std_fd;

	if (redir->tok_type == HEREDOC || redir->tok_type == REDIR_IN)
		std_fd = STDIN_FILENO;
	else
		std_fd = STDOUT_FILENO;
	fd = get_redir_fd(redir);
	if (fd == -2)
		return (0);
	if (fd == -1)
		return (sys_error(NULL, redir->file, strerror(errno)));
	dup2(fd, std_fd);
	close(fd);
	return (0);
}

/**
 * @brief Iterates through all redirections and applies them.
 *
 * Traverses the redirection linked list and calls handle_redir for each.
 * Stops and returns 1 if any redirection fails.
 *
 * @param redir Pointer to the start of the redirection linked list.
 * @return 0 on success, 1 on failure.
 */
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
