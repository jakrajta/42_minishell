#include "minishell.h"

char	*triple_strjoin(const char *s1, const char *s2, const char *s3)
{
	char	*joined;
	char	*temp;
	int		total_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	joined = malloc(sizeof(char) * (total_len + 1));
	if (!joined)
		return (NULL);
	temp = joined;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	while (*s3)
		*temp++ = *s3++;
	*temp = '\0';
	return (joined);
}
