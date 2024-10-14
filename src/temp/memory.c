#include "minishell.h"

void	free_array(char **s)
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
