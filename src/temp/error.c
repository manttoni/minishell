#include "minishell.h"

int	error_return(char *error_message)
{
	printf("%s\n", error_message);
	return (0);
}
