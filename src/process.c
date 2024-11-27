/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:49 by amaula            #+#    #+#             */
/*   Updated: 2024/11/27 12:50:23 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fork fail: returns to main and program finishes
 * Fork success: splits into two processes
 * child goes to run_child
 * parent goes to run to make more children */
int	do_fork(t_run *run)
{
	run->pids[run->i] = fork();
	if (run->pids[run->i] == -1)
	{
		close_pipes(run->pipefds, run->len);
		free_run(run);
		return (-1);
	}
	if (run->pids[run->i] == 0)
		run_child(run);
	return (run->pids[run->i]);
}

void	check_interrupt(t_main *main_struct)
{
	if (g_signal == 5)
	{
		main_struct->env->exit_code = 131;
		g_signal = 0;
	}
}

void	run_child(t_run *run)
{
	run->cmd_curr->path = find_path(run->cmd_curr, run->env);
	if (run->cmd_curr->path == NULL)
	{
		free_run(run);
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
	int		i;
	char	*last_cmd;

	last_cmd = last_command(run->cmd_list)->args[0];
	i = 0;
	while (i < run->len)
	{
		if (run->pids[i] >= 0)
			waitpid(run->pids[i], &(run->status), 0);
		if (i == run->len - 1)
		{
			if (ft_strcmp(last_cmd, "cd") != 0
				&& ft_strcmp(last_cmd, "export") != 0
				&& ft_strcmp(last_cmd, "unset") != 0
				&& ft_strcmp(last_cmd, "exit") != 0
				&& WIFEXITED(run->status))
				run->env->exit_code = WEXITSTATUS(run->status);
		}
		i++;
	}
	free(run->pids);
}
