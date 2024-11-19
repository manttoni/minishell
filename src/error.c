#include "minishell.h"

int	error_return(char *error_message)
{
	printf("%s\n", error_message);
	return (0);
}

char	*print_error(char *s, int n)
{
	if (n == 2)
	{
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	if (n == 1)
	{
		write(2, "-minishell: ", 12);
		write(2, s, ft_strlen(s));
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	}
	else if (n == 0)
	{
		write(2, "-minishell: ", 12);
		write(2, s, ft_strlen(s));
	}
	return (0);
}
