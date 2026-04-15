#include "minishell.h"

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

void	free_redir_list(t_redir **redir)
{
	t_redir	*temp;

	if (!redir || !*redir)
		return ;
	while (*redir)
	{
		temp = (*redir)->next;
		if((*redir)->file)
			free((*redir)->file);
		free(*redir);
		*redir = temp;
	}
	*redir = NULL;
}

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
	free(*shell);
	*shell = NULL;
}
