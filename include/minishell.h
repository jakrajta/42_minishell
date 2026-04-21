#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>

// #define BOLDCYAN "\033[1;36m"
// #define BOLDWHITE "\033[1;37m"
// #define RESET "\033[0m"
// #define PROMPT BOLDCYAN "minishell" BOLDWHITE "$"
# define PROMPT "$ "
# define SEPARATOR " \t\n\v\f\r"
# define METACHARS "|<>"

extern int	g_status;

typedef enum e_builtin
{
	B_NONE = 0,
	B_PWD,
	B_EXIT,
	B_ECHO,
	B_CD,
	B_ENV,
	B_EXPORT,
	B_UNSET
}	t_builtin;

typedef enum e_token
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	WORD
}	t_token;

typedef struct s_redir
{
	t_token			tok_type;      // type of token as in enum e_token
	int				heredoc_fd;    // stores fd[0]
	char			*file;         // malloced by strdup
	struct s_redir	*next;
}	t_redir;

// one cmd node is until pipe
typedef struct s_cmd
{
	char			**tokens;		// clear tokens without quotes until pipe
	int				tokens_count;   // tokes count until pipe
	char			*valid_path;    // final path to binary command, e.g. /usr/bin/ls
	int				skip_exec;      // flag for skip execution in case of echo jana > $FILE, when FILE var is empty
	t_builtin		builtin;
	t_redir			*redir;         // includes redirs with files / heredocs with deliminer 
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char	**env_copy;            // initial copy of bash environment variables
	char	**split_paths;         // splitted paths by ":" /usr/bin:/usr/sbin:
	char	*pwd;
	char	*old_pwd;
}	t_env;

typedef struct s_shell
{
	char			*cmd_line;     // stores initial input from user
	char			**all_tokens;  // cmd line splitted to tokens with quotes and expanded $VARS and $?
	int				last_exit_status;
	int				prev_fd;       // stores last fd[0] of pipeline after new pipe_fds{2] are created
	pid_t			last_pid;      // stores last pid, this pid is to be used for parent to clean processes
	t_cmd			*cmd;
	t_env			*env;
	struct termios	original_term; // original tty setting backup (for toggle ECHOCTL)
}	t_shell;

/* *** BUILTIN FCE *** */
int			execute_cd(t_cmd *cmd, t_shell *shell);
int			execute_echo(t_cmd *cmd);
int			execute_env(t_cmd *cmd, t_shell *shell);
int			execute_exit(t_cmd *cmd, t_shell *shell);
int			execute_export(t_cmd *cmd, t_shell *shell);
int			execute_pwd(t_env *env);
int			execute_unset(t_cmd *cmd, t_shell *shell);
t_builtin	get_builtin_type(char *cmd);

/* *** ENV FCE *** */
char		**add_new_env_var(char **env, char *new_var);
char		**copy_env(char **envp);
int			find_env_index(char **env, char *name);
char		*get_env_value(char *name, char **env_copy);
int			is_env_name(char *str);
void		update_env_value(char *var_name, char *value, t_env *env);

/* *** ERRORS_FREE *** */
int			display_error(char *msg);
int			sys_error(char *cmd, char *arg, char *msg);
int			display_warning(char *delimiter);
void		free_array(char **ptrs_array);
void		free_cmd_list( t_cmd **cmd);
void		free_env(t_env **env);
void		free_redir_list(t_redir **redir);
void		free_shell(t_shell **shell);

/* *** EXECUTION *** */
void		child_process(int pipe_fds[2], t_cmd *current,	t_shell *shell);
void		close_heredoc_fd(t_cmd *cmd);
int			execute_binary(t_cmd *cmd, t_shell *shell);
int			execute_builtin(t_cmd *cmd, t_shell *shell);
void		execute_commands(t_shell *shell);
int			execute_heredoc(t_cmd *cmd);
int			execute_pipeline(t_shell *shell);
int			execute_redir(t_redir *redir);
char		*get_cmd_path(t_shell *shell, char *cmd);
int			is_dir(char *path);
void		parent_process(int *prev_fd, int pipe_fds[2], t_cmd *current);
void		wait_for_all_children(t_shell *shell);

/* *** LEXER *** */
int			check_quotes_error(char **tokens, t_shell *shell);
char		*get_env_var_name(char *cmd_token);
char		*expand_token(char *token, t_shell *shell);
char		**split_to_tokens(char *str);
void		store_expanded_tokens(char **tokens, t_shell *shell);

/* *** MAIN *** */
void		handle_shlvl(t_shell *shell);
t_env		*init_env(char **envp);
t_shell		*init_shell(char **envp);
void		process_input(t_shell *shell);
char		*read_input(t_shell *shell);
void		shell_setup(t_shell *shell);
void		toggle_echoctl(int enable);

/* *** PARSER *** */
int			check_syntax_error(t_shell *shell);
t_cmd		*fill_cmd_list(t_shell *shell);
void		fill_tokens_redirs(t_cmd *cmd, char **tokens, int *i);
t_token		get_token_type(char *token);
t_cmd		*init_cmd(char **all_tokens_start, int *i);
t_redir		*init_redir_struct(char *token);
void		remove_quotes(char *str);

/* *** SIGNALS *** */
void		heredoc_signal_setup(void);
void		child_signal_setup(void);
void		parent_signal_setup(void);
void		signal_setup(void);

/* *** UTILS *** */
int			count_words(char *str, char *set);
char		**general_split(char *str, char *set);
int			is_double_redir(char *str);
int			is_in_set(char *set, char c);
t_redir		*init_redir_struct(char *token);
int			is_redirection(char *token);
int			my_strcmp(const char *s1, const char *s2);
int			tokens_count(char **array);
char		*triple_strjoin(const char *s1, const char *s2, const char *s3);

#endif