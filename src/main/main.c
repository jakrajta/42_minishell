#include "minishell.h"

/**
 * @brief Performs final cleanup before exiting the shell.
 *
 * Restores the terminal to its original state (if in interactive mode),
 * clears the readline history, frees all shell-allocated resources,
 * and returns the last recorded exit status.
 *
 * @param shell Pointer to the shell structure to be cleaned up.
 * @return The final exit status code of the shell.
 */
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

/**
 * @brief Entry point of the Minishell application.
 *
 * Initializes the shell environment, sets up signal handling and terminal
 * configurations. Enters the main execution loop: reads input, processes 
 * tokens, executes commands, and manages memory. Terminates upon EOF.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment variable array.
 * @return Exit status of the shell program.
 */
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
	while (1)
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
