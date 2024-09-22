#include "minishell.h"

void	free_split(char **s)
{
	char	**ptr;

	ptr = s;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(s);
}
