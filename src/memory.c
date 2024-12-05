/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:37 by amaula            #+#    #+#             */
/*   Updated: 2024/12/05 08:05:33 by amaula           ###   ########.fr       */
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
	close_pipes(run->pipefds, run->len);
	free_array(run->env->arr);
	free(run->env);
	free(run->pids);
	free_list(run->cmd_list);
	free(run);
	clear_history();
}

void	*free_env(t_env *env)
{
	free_array(env->arr);
	free(env);
	return (NULL);
}

void	*tokenizer_norm_free(t_token *new, t_token *start)
{
	free_token_list(start);
	free(new);
	return (NULL);
}
