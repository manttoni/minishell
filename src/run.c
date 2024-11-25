/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:45 by amaula            #+#    #+#             */
/*   Updated: 2024/11/25 15:55:55 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_run_norm(t_main *main_struct, t_run *run)
{
	run->cmd_curr = main_struct->cmd_list;
	run->cmd_list = main_struct->cmd_list;
	run->len = list_len(run->cmd_list);
	run->env = main_struct->env;
	run->pids = malloc(run->len * sizeof(pid_t));
	run->pipefds = allocate_pipefds(run->len);
}

/* memset pids to -2 explanation:
 * 	in case of builtin, it stays at -2,
 * 	then waitpids will not wait for it,
 * 	because builtins are run in parent process */
static t_run	*init_run(t_main *main_struct)
{
	t_run	*run;

	signal(SIGINT, fork_sig_handler);
	signal(SIGQUIT, fork_sig_handler);
	if (!*main_struct->cmd_list->args[0])
		return (NULL);
	run = malloc(sizeof(t_run));
	if (run == NULL)
		return (NULL);
	init_run_norm(main_struct, run);
	if (run->pids == NULL || run->pipefds == NULL
		|| create_pipes(run->pipefds, run->len) == 0)
	{
		free(run->pids);
		free_pipefds(run->pipefds, run->len);
		free(run);
		return (NULL);
	}
	ft_memset(run->pids, -2, run->len * sizeof(pid_t));
	run->i = 0;
	run->builtin = 0;
	return (run);
}

/* Runs a builtin and sets exit_code. */
static void	run_builtin(t_command *cmd, t_env *env)
{
	if (ft_strcmp("cd", cmd->args[0]) == 0)
		env->exit_code = ft_cd(cmd->args, env);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
		env->exit_code = ft_export(cmd->args + 1, env);
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
		env->exit_code = ft_unset(cmd->args + 1, env);
}

/* Return values:
 *	0: its not a builtin
 *	1: cd
 *	2: export
 *	3: unset
 */
int	is_builtin(t_command *cmd, t_env *env)
{
	char	*builtins[4];
	int		i;

	builtins[0] = "cd";
	builtins[1] = "export";
	builtins[2] = "unset";
	i = 0;
	while (i < 3)
	{
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
		{
			run_builtin(cmd, env);
			return (i + 1);
		}
		i++;
	}
	return (0);
}

int	run(t_main *main_struct)
{
	t_run	*run;

	run = init_run(main_struct);
	if (run == NULL)
		return (0);
	while (run->cmd_curr)
	{
		run->builtin = 0;
		if (run->cmd_curr->index == run->len - 1)
			run->builtin = is_builtin(run->cmd_curr, run->env);
		if (run->builtin == 0)
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
