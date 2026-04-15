#include "minishell.h"

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
	if (cmd_line && *cmd_line)
		add_history(cmd_line);
	return (cmd_line);
}

static void	clean_tokens(char **tokens, t_shell *shell)
{
	if (tokens)
		free_array(tokens);
	shell->all_tokens = NULL;
}

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
