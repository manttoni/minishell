#include "minishell.h"

static t_run	*init_run(t_command *cmd_list, t_env *env)
{
	t_run	*run;

	run = malloc(sizeof(t_run));
	if (run == NULL)
		return (NULL);
	run->cmd_curr = cmd_list;
	run->env = env;
	run->pids = malloc(list_len(cmd_list) * sizeof(pid_t));
	run->pipefds = allocate_pipefds(list_len(cmd_list));
	if (run->pids == NULL || run->pipefds == NULL)
	{
		free(run->pids);
		free_pipefds(run->pipefds, run->len);
		free(run);
		return (NULL);
	}
	run->i = 0;
	run->len = list_len(cmd_list);
	return (run);
}

int	do_fork(t_run *run)
{
	run->pids[run->i] = fork();
	if (run->pids[run->i] == -1)
	{
		close_pipes(run->pipefds, run->len);
		free(run->pids);
		return (0);
	}
	return (1);
}

void	free_run(t_run *run)
{
	close_pipes(run->pipefds, run->len);
	free_array(run->env->arr);
	free(run->env);
	free_list(run->cmd_list);
	clear_history();
}

void	run_child(t_run *run)
{
	run->cmd_curr->path = find_path(run->cmd_curr, run->env);
	if (!(run->cmd_curr->path))
	{
		free_run(run);
		exit(ERR_CMD_NOT_FOUND);
	}
	set_io(run->cmd_curr, run->pipefds);
	close_pipes(run->pipefds, run->len);
	execve(run->cmd_curr->path, run->cmd_curr->args, run->env->arr);
	free_run(run);
	exit(ERR_EXEC);
}

void wait_pids(t_run *run)
{
	int	i;

	i = 0;
	while(i < run->len)
	{
		waitpid(run->pids[i], &(run->status), 0);
		if (i == run->len - 1)
		{
			if (WIFEXITED(run->status))
				run->env->exit_code = WEXITSTATUS(run->status);
			else if (WIFSIGNALED(run->status))
				run->env->exit_code = 128 + WTERMSIG(run->status);
		}
		i++;
	}
	free(run->pids);
}

int	run(t_command *cmd_list, t_env *env)
{
	t_run	*run;
	int		builtin_ret;

	builtin_ret = run_builtin(cmd_list->args, env);
	if (builtin_ret >= 0) // it was a builtin. if not builtin, returns -1
		return (builtin_ret);
	run = init_run(cmd_list, env);
	if (run == NULL)
		return (0);
	if (create_pipes(run->pipefds, run->len) == 0)
		return (0);
	while (run->cmd_curr)
	{
		if (do_fork(run) == 0) // fail
			return (0);
		if (run->pids[run->i] == 0) // child
			run_child(run);
		run->i++;
		run->cmd_curr = run->cmd_curr->next;
	}
	close_pipes(run->pipefds, run->len);
	wait_pids(run);
	free(run);
	return (1);
}
