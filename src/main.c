#include "minishell.h"

void debug_print_commands(t_cmd *cmd)
{
    int i;
    t_redir *r;
    int node_count = 0;

    while (cmd)
    {
        printf("\n\033[1;34m--- COMMAND NODE %d ---\033[0m\n", node_count++);
        
        // Kontrola tokenů (to, co půjde do execve)
        printf("  Tokens: ");
        if (cmd->tokens)
        {
            for (i = 0; cmd->tokens[i]; i++)
                printf("[%s] ", cmd->tokens[i]);
        }
        else
            printf("(null)");
        
        // Kontrola vlajek a typu
        printf("\n  Builtin: %d | Skip Exec: %s\n", 
               cmd->builtin, cmd->skip_exec ? "\033[0;31mANO\033[0m" : "NE");

        // Kontrola redirekcí
        r = cmd->redir;
        if (!r)
            printf("  Redirekce: (žádné)\n");
        while (r)
        {
            printf("  \033[1;33mRedir:\033[0m type=%d, file=[%s]\n", r->tok_type, r->file);
            r = r->next;
        }
        cmd = cmd->next;
    }
    printf("\033[1;34m-----------------------\033[0m\n\n");
}

static char *get_user_input(t_shell *shell)
{
	char *cmd_line;
	char *prompt;

	if (isatty(STDIN_FILENO))  // user writes directly to terminal 
		prompt = PROMPT;
	else 
		prompt = NULL;    //noninteractive, doesnt display prompt eg.  echo "pwd" | ./minishell

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

	shell = init_shell(envp);
	if (!shell)
		return (1);
	handle_shlvl(shell);
	signal_setup();
	while(1)
	{
		shell->cmd_line = get_user_input(shell);
		if (!shell->cmd_line) // signal CTR + D
		{
			if (isatty(STDIN_FILENO))  //exit displayed only if user writes directly to termninal
				ft_putstr_fd("exit\n", 2); 
			break;
		}
		if (shell->cmd_line[0])
		{
			tokens_with_quotes = split_to_tokens(shell->cmd_line);
			if (tokens_with_quotes == NULL)
			{
				free(shell->cmd_line);
				continue;
			}
			if (check_quotes_error(tokens_with_quotes, shell))
			{
				free_array(tokens_with_quotes);
				free(shell->cmd_line);
				continue;	
			}
			finalize_tokens(tokens_with_quotes, shell);
			shell->all_tokens = tokens_with_quotes;
			printf("DEBUG: Mam tokeny, jdu na syntax check\n");
			if (check_syntax_error(shell))
			{
				free_array(shell->all_tokens);  
				free(shell->cmd_line);
				shell->all_tokens = NULL;
				tokens_with_quotes = NULL;
				continue;
			}
			printf("DEBUG: Syntax OK, jdu plnit strukturu\n");
			if (tokens_with_quotes && tokens_with_quotes[0])
				shell->cmd = fill_cmd_list(shell);
			if (shell->cmd)
			{
				printf("DEBUG: Struktura naplnena, tisknu:\n");
				debug_print_commands(shell->cmd);
				//execute_commands(shell);
				free_cmd_list(&shell->cmd);
			}
			if (shell->all_tokens)
			{
				free_array(shell->all_tokens);
				shell->all_tokens = NULL; 
				tokens_with_quotes = NULL;
			}		
		}	
		free(shell->cmd_line); 
 	}
	rl_clear_history();
	free_shell(&shell);
	return (0);
}