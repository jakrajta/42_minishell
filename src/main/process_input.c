#include "minishell.h"

/**
 * @brief Reads a line of input from the user using readline.
 *
 * Handles prompt display (only in interactive mode), manages global signal 
 * status updates, and adds non-empty commands to the history.
 *
 * @param shell Pointer to the shell structure (for exit status management).
 * @return A string containing the user input, or NULL on EOF/error.
 */

char	*read_input(t_shell *shell)
{
	char	*cmd_line;
	char	*prompt;

	if (isatty(STDIN_FILENO))
		prompt = PROMPT;
	else
		prompt = NULL;
	cmd_line = readline(prompt);
	if (g_status != 0)
	{
		shell->last_exit_status = g_status;
		g_status = 0;
	}
	if (cmd_line && *cmd_line && isatty(STDIN_FILENO))
		add_history(cmd_line);
	return (cmd_line);
}

/* char	*read_input(t_shell *shell)
{
	char	*cmd_line;
	size_t	len;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		cmd_line = readline(PROMPT);
	else
		cmd_line = get_next_line(STDIN_FILENO);
	if (!cmd_line)
		return (NULL);
	len = ft_strlen(cmd_line);
	if (len > 0 && cmd_line[len - 1] == '\n')
		cmd_line[len - 1] = '\0';
	if (g_status != 0)
	{
		shell->last_exit_status = g_status;
		g_status = 0;
	}
	if (cmd_line && *cmd_line && isatty(STDIN_FILENO))
		add_history(cmd_line);
	return (cmd_line);
} */

/**
 * @brief Frees the token array and resets the shell token pointer.
 *
 * Helper function to safely deallocate the array of strings and 
 * ensure the shell structure does not hold dangling pointers.
 *
 * @param tokens The array of tokens to free.
 * @param shell Pointer to the shell structure.
 */
static void	clean_tokens(char **tokens, t_shell *shell)
{
	if (tokens)
		free_array(tokens);
	shell->all_tokens = NULL;
}

/**
 * @brief Manages the entire input lifecycle: parsing, validation, and execution.
 *
 * Orchestrates the sequence of processing: tokenizing, checking for quote 
 * errors, expansion, syntax validation, command list generation, 
 * execution, and finally memory cleanup.
 *
 * @param shell Pointer to the shell structure.
 */
void	process_input(t_shell *shell)
{
	char	**tokens;

	tokens = split_to_tokens(shell->cmd_line);
	if (!tokens)
		return ;
	if (check_quotes_error(tokens, shell))
	{
		clean_tokens(tokens, shell);
		return ;
	}
	store_expanded_tokens(tokens, shell);
	if (check_syntax_error(shell))
	{
		clean_tokens(shell->all_tokens, shell);
		return ;
	}
	shell->cmd = fill_cmd_list(shell);
	if (shell->cmd)
	{
		execute_commands(shell);
		free_cmd_list(&shell->cmd);
	}
	clean_tokens(shell->all_tokens, shell);
}
