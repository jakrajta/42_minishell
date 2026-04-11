CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft

#Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Library Readline
LIBS = -lreadline
LIBFT = libft/libft.a

# Source directories
SRC_DIR = src
OBJ_DIR = build

# Source files 
SRC = builtins/builtins.c \
	  builtins/exec_cd.c \
	  builtins/exec_env.c \
	  builtins/exec_echo.c \
	  builtins/exec_exit.c \
	  builtins/exec_export.c \
	  builtins/exec_pwd.c \
	  builtins/exec_unset.c \
	  env/add_new_env_var.c \
	  env/copy_env.c \
	  env/find_env_index.c \
	  env/get_env_value.c \
	  env/is_env_name.c \
	  env/update_env_value.c \
	  errors_free/display_error.c \
	  errors_free/free_fce.c \
	  execution/child_process.c \
	  execution/exec_binary.c \
	  execution/exec_builtin.c \
	  execution/exec_commands.c \
	  execution/exec_heredoc.c \
	  execution/exec_pipeline.c \
	  execution/exec_redir.c \
	  execution/get_path.c \
	  execution/parent_process.c \
	  expansion/expand_all.c \
	  expansion/get_env_var_name.c \
	  lexer/check_quotes_error.c \
	  lexer/finalize_tokens.c \
	  lexer/split_to_tokens.c \
	  parser/check_syntax_error.c \
	  parser/fill_cmd_list.c \
	  parser/fill_cmdtokens_redirs.c \
	  parser/get_token_type.c \
	  parser/init_cmd.c \
	  parser/init_redir.c \
	  parser/remove_quotes.c \
	  setup/handle_shlvl.c \
	  setup/init_env.c \
	  setup/init_shell.c \
	  signals/signals.c \
	  signals/heredoc_signals.c \
	  utils/general_split.c \
	  utils/triple_join.c \
	  utils/utils1.c \
	  minishell.c \
	
# Object files (automatically fill of prefic src/)
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME = minishell

# Default target
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C libft

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS)
	@echo "$(GREEN)Minishell is ready! $(RESET)"

# Build final binary
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	
# Removing .o
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C libft clean
	@echo "$(RED)Object files removed! $(RESET)"

# Full cleaning
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C libft fclean
	@echo "$(RED)All binaries removed! 💀$(RED)"

# Recompilation
re: fclean all

.PHONY: all clean fclean re

.SILENT: