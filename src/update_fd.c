/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:59 by amaula            #+#    #+#             */
/*   Updated: 2024/11/21 11:23:42 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd	*init_fd(t_data *data)
{
	t_fd	*fdstr;

	if (data->token_curr->next == NULL
		|| data->token_curr->next->type != WORD)
	{
		print_error("syntax error: invalid file name / delimiter", 0);
		return (NULL);
	}
	fdstr = malloc(sizeof(t_fd));
	if (fdstr == NULL)
		return (NULL);
	fdstr->filename = data->token_curr->next->string;
	fdstr->type = data->token_curr->type;
	fdstr->command = data->cmd_curr;
	return (fdstr);
}

static int	update_fdin(t_fd *fd, t_data *data)
{
	if (fd->command->fdin > 2)
		close(fd->command->fdin);
	if (fd->type == IN)
	{
		fd->command->fdin = open(fd->filename, O_RDONLY);
		if (fd->command->fdin < 0)
			print_error(fd->filename, 1);
	}
	else
		fd->command->fdin = handle_heredoc_redirection(fd, data);
	if (fd->command->fdin < 0)
		return (0);
	return (1);
}

static int	update_fdout(t_fd *fdstr)
{
	int	fd;

	if (fdstr->command->fdout > 2)
		close(fdstr->command->fdout);
	if (fdstr->type == OUT)
		fd = open(fdstr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(fdstr->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		print_error(fdstr->filename, 1);
		return (0);
	}
	fdstr->command->fdout = fd;
	return (1);
}

int	update_fd(t_data *data)
{
	t_fd	*fd;
	int		ret;

	fd = init_fd(data);
	if (fd == NULL)
	{
		free_list(data->cmd_list);
		free(data);
		return (0);
	}
	if (fd->type == IN || fd->type == HEREDOC)
		ret = update_fdin(fd, data);
	else
		ret = update_fdout(fd);
	free(fd);
	if (ret == 0)
	{
		free_list(data->cmd_list);
		data->env->exit_code = 1;
		free(data);
		return (ret);
	}
	data->token_curr = data->token_curr->next;
	return (ret);
}
