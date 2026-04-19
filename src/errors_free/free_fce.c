#include "minishell.h"

/**
 * @brief Frees a NULL-terminated array of strings and the array itself.
 *
 * @param ptrs_array The pointer to the array of strings to be freed.
 */
void	free_array(char **ptrs_array)
{
	char	**temp;

	if (!ptrs_array)
		return ;
	temp = ptrs_array;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(ptrs_array);
}

/**
 * @brief Frees the redirection linked list and all its nodes.
 *
 * This function iterates through the redirection list, frees the 
 * filename string in each node, and then the node itself.
 * Sets the pointer to NULL afterwards.
 *
 * @param redir Pointer to the head of the redirection list.
 */
void	free_redir_list(t_redir **redir)
{
	t_redir	*temp;

	if (!redir || !*redir)
		return ;
	while (*redir)
	{
		temp = (*redir)->next;
		if ((*redir)->file)
			free((*redir)->file);
		free(*redir);
		*redir = temp;
	}
	*redir = NULL;
}

/**
 * @brief Frees the command linked list and all its associated data.
 *
 * Recursively (or iteratively) frees tokens, paths, and redirections 
 * for each command node, then frees the node itself.
 * Sets the pointer to NULL afterwards.
 *
 * @param cmd Pointer to the head of the command list.
 */
void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		temp = (*cmd)->next;
		if ((*cmd)->tokens)
			free_array((*cmd)->tokens);
		if ((*cmd)->valid_path)
			free((*cmd)->valid_path);
		if ((*cmd)->redir)
			free_redir_list((&(*cmd)->redir));
		free(*cmd);
		*cmd = temp;
	}
	*cmd = NULL;
}

/**
 * @brief Frees the environment structure and its allocated fields.
 *
 * Releases memory for path splits, environment copies, and PWD records.
 *
 * @param env Pointer to the environment structure.
 */
void	free_env(t_env **env)
{
	if (!env || !(*env))
		return ;
	if ((*env)->split_paths)
		free_array((*env)->split_paths);
	if ((*env)->env_copy)
		free_array((*env)->env_copy);
	if ((*env)->pwd)
		free((*env)->pwd);
	if ((*env)->old_pwd)
		free((*env)->old_pwd);
	free(*env);
	*env = NULL;
}

/**
 * @brief Frees the entire shell structure and all allocated resources.
 *
 * This is the primary cleanup function for the shell. It releases 
 * the command line, tokens, command list, and environment structure
 * and close pref_id if exists.
 *
 * @param shell Pointer to the main shell structure.
 */
void	free_shell(t_shell **shell)
{
	if (!shell || !(*shell))
		return ;
	if ((*shell)->cmd_line)
		free((*shell)->cmd_line);
	if ((*shell)->all_tokens)
		free_array((*shell)->all_tokens);
	if ((*shell)->cmd)
		free_cmd_list(&((*shell))->cmd);
	if ((*shell)->env)
		free_env(&((*shell))->env);
	if ((*shell)->prev_fd != -1)
		close ((*shell)->prev_fd);
	free(*shell);
	*shell = NULL;
}
