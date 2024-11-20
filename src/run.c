#include "minishell.h"

static t_run	*init_run(t_main *main_struct)
{
	t_run	*run;

	run = malloc(sizeof(t_run));
	if (run == NULL)
		return (NULL);
	run->cmd_curr = main_struct->cmd_list;
	run->cmd_list = main_struct->cmd_list;
	run->len = list_len(run->cmd_list);
	run->env = main_struct->env;
	run->pids = malloc(run->len * sizeof(pid_t));
	run->pipefds = allocate_pipefds(run->len);
	if (run->pids == NULL || run->pipefds == NULL
		|| create_pipes(run->pipefds, run->len) == 0)
	{
		free(run->pids);
		free_pipefds(run->pipefds, run->len);
		free(run);
		return (NULL);
	}
	run->i = 0;
	return (run);
}

int	run_builtin(char **args, t_env *env)
{
	if (ft_strcmp("cd", args[0]) == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp("export", args[0]) == 0)
		return (ft_export(args + 1, env));
	else if (ft_strcmp("unset", args[0]) == 0)
		return (ft_unset(args + 1, env));
	else if (ft_strcmp("env", args[0]) == 0)
		return (ft_env(env));
	return (-1);
}

int	run(t_main *main_struct)
{
	t_run	*run;
	int		builtin_ret;

	builtin_ret = run_builtin(main_struct->cmd_list->args, main_struct->env);
	if (builtin_ret >= 0)
	{
		main_struct->env->exit_code = builtin_ret;
		return (builtin_ret);
	}
	run = init_run(main_struct);
	if (run == NULL)
		return (0);
	while (run->cmd_curr)
	{
		if (do_fork(run) == -1)
			return (0);
		if (run->pids[run->i] == 0)
			run_child(run, main_struct);
		run->i++;
		run->cmd_curr = run->cmd_curr->next;
	}
	close_pipes(run->pipefds, run->len);
	wait_pids(run);
	free(run);
	return (1);
}
