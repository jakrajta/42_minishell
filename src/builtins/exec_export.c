#include "minishell.h"

/**
 * @brief Swaps two string pointers.
 */
static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Creates a sorted copy of the environment array pointers.
 */
static char	**sort_env(char **env)
{
	char	**sorted;
	char	**array;
	char	**temp;
	int		len;

	len = tokens_count(env);
	sorted = malloc(sizeof(char *) * (len + 1));
	if (!sorted)
		return (NULL);
	array = sorted;
	while (len-- > 0)
		*array++ = *env++;
	*array = NULL;
	while (--array > sorted)
	{
		temp = sorted;
		while (temp < array)
		{
			if (my_strcmp(*temp, *(temp + 1)) > 0)
				swap(temp, (temp + 1));
			temp++;
		}
	}
	return (sorted);
}

/**
 * @brief Prints the sorted environment variables in export format.
 *
 * Formats each variable as 'declare -x NAME="VALUE"'. If the variable 
 * has no value (no '='), it only prints 'declare -x NAME'.
 *
 * @param sorted_env The sorted array of environment strings.
 */
static void	print_export_sorted_env(char **sorted_env)
{
	int	i;
	int	j;

	i = 0;
	while (sorted_env && sorted_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (sorted_env[i][j] && sorted_env[i][j] != '=')
			j++;
		write(1, sorted_env[i], j);
		if (sorted_env[i][j] == '=')
		{
			write(1, "=\"", 2);
			ft_putstr_fd(&sorted_env[i][j + 1], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

/**
 * @brief Handles the export command with no arguments.
 *
 * Sorts a copy of the environment array and prints it using the 
 * 'declare -x' format. Memory allocated for the sorted array is freed.
 *
 * @param env The current environment array.
 * @return int 0 on success, 1 on allocation failure.
 */
static int	export_no_args(char **env)
{
	char	**sorted_env;

	sorted_env = sort_env(env);
	if (!sorted_env)
		return (1);
	print_export_sorted_env(sorted_env);
	free(sorted_env);
	return (0);
}

/**
 * @brief Executes the export builtin command.
 *
 * If no arguments are provided, it displays the sorted environment.
 * Otherwise, it iterates through arguments, validates them, and 
 * either updates an existing variable or adds a new one.
 *
 * @param cmd Pointer to the command structure.
 * @param shell Pointer to the shell structure.
 * @return int Always returns 0.
 */
int	execute_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	env_index;

	if (cmd->tokens_count == 1)
		return (export_no_args(shell->env->env_copy), 0);
	i = 0;
	while (cmd->tokens[++i])
	{
		env_index = find_env_index(shell->env->env_copy, cmd->tokens[i]);
		if (!is_env_name(cmd->tokens[i]))
			sys_error(cmd->tokens[0], cmd->tokens[i], "not a valid identifier");
		else if (env_index >= 0)
		{
			free(shell->env->env_copy[env_index]);
			shell->env->env_copy[env_index] = ft_strdup(cmd->tokens[i]);
		}
		else
			shell->env->env_copy = add_new_env_var(shell->env->env_copy,
					cmd->tokens[i]);
	}
	return (0);
}
