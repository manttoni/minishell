#include "minishell.h"

void	free_split(char **s)
{
	char	**ptr;

	if (s == NULL)
		return ;
	ptr = s;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(s);
}
