/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:35:00 by amaula            #+#    #+#             */
/*   Updated: 2024/12/05 16:59:12 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipefds(int **pipefds, int len)
{
	int	i;

	if (pipefds == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		if(pipefds + i)
			free(pipefds[i]);
		pipefds[i] = 0;
		i++;
	}
	free(pipefds);
}

int	create_pipes(int **pipefds, int cmds)
{
	int	i;

	i = 0;
	while (i < cmds - 1)
	{
		if (pipe(pipefds[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

void	close_pipes(int **pipefds, int cmds)
{
	int	i;

	i = 0;
	while (i < cmds - 1)
	{
		if ((close(pipefds[i][1]) == -1) || close(pipefds[i][0]) == -1)
			print_error("unable to close pipefds", 0);
		i++;
	}
	free_pipefds(pipefds, cmds);
	pipefds = 0;
}

int	set_io(t_command *command, int **pipefds)
{
	int	ret;

	ret = 0;
	if (command->fdin != 0)
		ret = ft_min(ret, dup2(command->fdin, STDIN_FILENO));
	else if (command->index != 0)
		ret = ft_min(ret, dup2(pipefds[command->index - 1][0], STDIN_FILENO));
	if (command->fdout != 1)
		ret = ft_min(ret, dup2(command->fdout, STDOUT_FILENO));
	else if (list_len(command) != 1)
		ret = ft_min(ret, dup2(pipefds[command->index][1], STDOUT_FILENO));
	if (command->fdin > 1)
		ret = close(command->fdin);
	if (command->fdout > 1)
		ret = close(command->fdout);
	if (ret == -1)
	{
		print_error("set_io() failed to execute", 0);
		return (1);
	}
	return (0);
}

int	**allocate_pipefds(int len)
{
	int	**pipefds;
	int	i;

	pipefds = malloc(len * sizeof(int *));
	if (pipefds == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		pipefds[i] = malloc(2 * sizeof(int));
		if (pipefds[i] == NULL)
		{
			free_pipefds(pipefds, i);
			return (NULL);
		}
		i++;
	}
	return (pipefds);
}
