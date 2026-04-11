#include "minishell.h"

static void	update_split_paths(t_env *env)
{
	char *new_paths;

	if(env->split_paths)
		free_array(env->split_paths);
	new_paths = get_env_value("PATH", env->env_copy);
	if (new_paths)
		env->split_paths = general_split(new_paths, ":");
	else
		env->split_paths = NULL;
}

//knihovna <sys/stat.h>
int is_dir(char *path)   
{
	struct stat   st;  //prazdna struktura pro zapsatni info o slozce

	if (stat(path, &st) == 0)     // stat zjisti podle path k slozce inco a ulozi do struktury  
		return (S_ISDIR(st.st_mode));  // makro.\, ktere podle infomaci rozhode jestli je to slozka  == 1 nebo  ne == 0
	return (0);   //vse ok, info o slozce
}

char *get_cmd_path(t_shell *shell, char *cmd)
//char *cmd = cmd->token[0] / v ls -la | grep "ahoj"  je to ls a grep
{
	char *full_path;
	int i;
	
	if (!shell || !cmd)
		return (NULL);
	// pokud je cesta zadana  cd 42/42_minishell/minishell
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)  // && is_dir(shell->all_tokens[0])) neni nutne childs process si to osefuje errnem
			return (ft_strdup(cmd));
		return (NULL);
	}
	// updatuju env->split_paths, nutne po update env->env_copy pomoci export/unset
	update_split_paths(shell->env);

	//  prikaz bez cesty napr. ls  ->v path hledame cestu k binarce prikazu (ls, cat...)
	i = 0;
	while (shell->env->split_paths && shell->env->split_paths[i])
	{
		full_path = triple_strjoin(shell->env->split_paths[i], "/", cmd);
		if (!full_path)
			return(NULL);
		if (full_path && access(full_path, X_OK) == 0 && !is_dir(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

