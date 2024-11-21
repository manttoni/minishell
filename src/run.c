/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:45 by amaula            #+#    #+#             */
/*   Updated: 2024/11/21 11:20:11 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_builtin(t_command *cmd)
{
	char	*builtins[4];
	int		i;

	builtins[0] = "cd";
	builtins[1] = "export";
	builtins[2] = "unset";
	builtins[3] = "env";
	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	norm_builtin(t_run *run)
{
	int	ec;

	if (run->cmd_curr->index == run->len - 1)
	{
		ec = run_builtin(run->cmd_curr->args, run->env);
		run->env->exit_code = ec;
	}
}

int	run(t_main *main_struct)
{
	t_run	*run;

	run = init_run(main_struct);
	if (run == NULL)
		return (0);
	while (run->cmd_curr)
	{
		if (is_builtin(run->cmd_curr))
			norm_builtin(run);
		else
		{
			if (do_fork(run) == -1)
				return (0);
			if (run->pids[run->i] == 0)
				run_child(run);
			run->i++;
		}
		run->cmd_curr = run->cmd_curr->next;
	}
	close_pipes(run->pipefds, run->len);
	wait_pids(run);
	free(run);
	return (1);
}
