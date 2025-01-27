/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:37 by amaula            #+#    #+#             */
/*   Updated: 2024/12/03 20:39:12 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **s)
{
	char	**ptr;

	if (s == NULL)
		return ;
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
	if (!run)
		return ;
	free_array(run->env->arr);
	free(run->env);
	free(run->pids);
	free_list(run->cmd_list);
	free(run);
	clear_history();
}
