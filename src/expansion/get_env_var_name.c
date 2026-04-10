#include "minishell.h"

/**
 * @brief Extracts the name of an environment variable from a string.
 * * This function identifies the valid identifier of an environment variable
 * following a '$' sign. According to shell rules, a valid name must start 
 * with a letter or an underscore, followed by alphanumeric characters 
 * or underscores.
 * * @param cmd_token The string starting at the first character after the '$'.
 * @return An allocated string containing the variable name, 
 * or NULL if the first character is invalid.
 */
char	*get_env_var_name(char *cmd_token)
{
	char	*name;
	char	*token_temp;
	int		len;

	token_temp = cmd_token;
	if (!token_temp || (*token_temp != '_' && !ft_isalpha(*token_temp)))
		return (NULL);
	len = 0;
	while (*token_temp != '\0' && (ft_isalnum(*token_temp)
			|| *token_temp == '_'))
	{
		len++;
		token_temp++;
	}
	name = ft_substr(cmd_token, 0, len);
	return (name);
}
