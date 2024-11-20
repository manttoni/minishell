#include "minishell.h"

int	do_fork(t_run *run)
{
	run->pids[run->i] = fork();
	if (run->pids[run->i] == -1)
	{
		close_pipes(run->pipefds, run->len);
		free_run(run);
		return (-1);
	}
	return (run->pids[run->i]);
}

void	run_child(t_run *run, t_main *main_struct)
{
	run->cmd_curr->path = find_path(run->cmd_curr, run->env);
	if (run->cmd_curr->path == NULL)
	{
		free_run(run);
		free(main_struct);
		exit(ERR_CMD_NOT_FOUND);
	}
	set_io(run->cmd_curr, run->pipefds);
	close_pipes(run->pipefds, run->len);
	execve(run->cmd_curr->path, run->cmd_curr->args, run->env->arr);
	free(run->cmd_curr->path);
	free_run(run);
	exit(ERR_EXEC);
}

void	wait_pids(t_run *run)
{
	int	i;

	i = 0;
	while (i < run->len)
	{
		waitpid(run->pids[i], &(run->status), 0);
		if (i == run->len - 1)
		{
			if (WIFEXITED(run->status))
				run->env->exit_code = WEXITSTATUS(run->status);
		}
		i++;
	}
	free(run->pids);
}
