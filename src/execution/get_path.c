#include "minishell.h"

/**
 * @brief Updates the cached split PATH directories.
 *
 * Frees the existing array of split paths and regenerates it by 
 * splitting the current "PATH" environment variable by the colon 
 * (':') delimiter.
 *
 * @param env Pointer to the environment structure.
 */
static void	update_split_paths(t_env *env)
{
	char	*new_paths;

	if (env->split_paths)
		free_array(env->split_paths);
	new_paths = get_env_value("PATH", env->env_copy);
	if (new_paths)
		env->split_paths = general_split(new_paths, ":");
	else
		env->split_paths = NULL;
}

/**
 * @brief Checks if a given path corresponds to a directory.
 *
 * Uses the stat system call to retrieve file mode information and 
 * determines if the path points to a directory.
 *
 * @param path The file path to check.
 * @return 1 if it is a directory, 0 otherwise.
 */
int	is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
		return (S_ISDIR(st.st_mode));
	return (0);
}

/**
 * @brief Resolves the full executable path for a given command.
 *
 * If the command contains a '/', it verifies the path directly.
 * Otherwise, it iterates through directories listed in the PATH 
 * environment variable to locate the executable.
 *
 * @param shell Pointer to the main shell structure.
 * @param cmd The command name or partial path to resolve.
 * @return The absolute path to the executable if found and executable, 
 * NULL otherwise.
 */
char	*get_cmd_path(t_shell *shell, char *cmd)
{
	char	*full_path;
	int		i;

	if (!shell || !cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	update_split_paths(shell->env);
	i = 0;
	while (shell->env->split_paths && shell->env->split_paths[i])
	{
		full_path = triple_strjoin(shell->env->split_paths[i], "/", cmd);
		if (!full_path)
			return (NULL);
		if (full_path && access(full_path, X_OK) == 0 && !is_dir(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
