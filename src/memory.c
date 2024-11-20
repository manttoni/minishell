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

void	free_run(t_run *run)
{
	close_pipes(run->pipefds, run->len);
	free_array(run->env->arr);
	free(run->env);
	free_list(run->cmd_list);
	clear_history();
}
