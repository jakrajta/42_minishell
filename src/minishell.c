#include "minishell.h"

static char *get_user_input(t_shell *shell)
{
	char *cmd_line;
	char *prompt;
	
	if (isatty(STDIN_FILENO))  // pokud uzivatel pise do terminalu 
		prompt = PROMPT;
	else 
		prompt = NULL;    //pokud napr echo "pwd" | ./minishell  nevypisuj
		
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

int main(int argc, char **argv, char **envp)
{
	t_shell *shell;
	char **tokens_with_quotes;

	if (argc != 1 || argv[1])
		return(display_error("Correct input: ./minishell"));

	shell = init_shell(envp);  // v nem uz inicalizovana struct env
	if (!shell)
		return (1);
	handle_shlvl(shell);
	signal_setup();
	while(1)
	{
		shell->cmd_line = get_user_input(shell);
		if (!shell->cmd_line)  // ctrl+d signal EOF = vstupni proud skoncil
		{
			if (isatty(STDIN_FILENO))  //pouze pokud uzivatel pise primo do terminalu
				ft_putstr_fd("exit\n", 2); // ctr + D  vrati NULL
			break;
		}
		if (shell->cmd_line[0])  // pokud uzivatel neco napsal
		{
			tokens_with_quotes = split_to_tokens(shell->cmd_line);
			if (tokens_with_quotes == NULL)
			{
				free(shell->cmd_line);
				continue;
			}
			//shell->total_tokens_count = tokens_count(tokens_with_quotes);
			if (check_quotes_error(tokens_with_quotes, shell))
			{
				free_array(tokens_with_quotes);
				free(shell->cmd_line);
				continue;	
			}
			finalize_tokens(tokens_with_quotes, shell);
			shell->all_tokens = tokens_with_quotes;
			if (check_syntax_error(shell))
			{
				free_array(shell->all_tokens);  //mallok na tokes_with_quotes, finalize_tokens je zbavi zavorek a prekopiruje pointery do alll_array
				free(shell->cmd_line);
				shell->all_tokens = NULL;  //nutny reset pro dalsi kolo
				tokens_with_quotes = NULL;
				continue;
			}
			if (tokens_with_quotes && tokens_with_quotes[0])
				shell->cmd = fill_cmd_list(shell);
			if (shell->cmd)
			{
				execute_commands(shell);
				free_cmd_list(&shell->cmd);
			}
			if (shell->all_tokens)
			{
				free_array(shell->all_tokens);
				shell->all_tokens = NULL;  //nutny reset pro dalsi kolo
				tokens_with_quotes = NULL;
			}		
		}	
		free(shell->cmd_line); 
 	}
	rl_clear_history();
	free_shell(&shell);
	return (0);
}