#include "minishell.h"

int	is_double_redir(char *str)
{
	return ((*str == '>' && *(str + 1) == '>')
		|| (*str == '<' && *(str + 1) == '<'));
}

int	is_in_set(char *set, char c)
{
	return (c != '\0' && ft_strchr(set, c) != NULL);
}

int	is_redirection(char *token)
{
	t_token	type;

	if (!token)
		return (0);
	type = get_token_type(token);
	if (type == WORD || type == PIPE)
		return (0);
	return (1);
}

int	tokens_count(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return (0);
	while (*array)
	{
		count++;
		array++;
	}
	return (count);
}

int	my_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
