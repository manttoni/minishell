#include "minishell.h"

int	create_pipes(int *pipefds, int cmds)
{
	int	i;

	i = 0;
	while (i < cmds - 1)
	{
		if (pipe(pipefds + 2 * i) == -1)
			return (error_return("pipe"));
		i++;
	}
	return (1);
}

void	close_pipes(int *pipefds, int cmds)
{
	int	i;

	i = 0;
	while (i < 2 * (cmds - 1))
	{
		close(pipefds[i]);
		i++;
	}
}
