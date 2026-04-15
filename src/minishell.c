#include "minishell.h"

static int	cleanup_exit(t_shell *shell)
{
	int	final_status;

	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("exit\n", 2);
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_term);
	}
	rl_clear_history();
	final_status = shell->last_exit_status;
	free_shell(&shell);
	return (final_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc > 1)
		return (display_error("Correct input: ./minishell"));
	shell = init_shell(envp);
	if (!shell)
		return (1);
	shell_setup(shell);
	while(1)
	{
		shell->cmd_line = read_input(shell);
		if (!shell->cmd_line)
			break ;
		if (shell->cmd_line[0])
			process_input(shell);
		free(shell->cmd_line);
	}
	return (cleanup_exit(shell));
}
