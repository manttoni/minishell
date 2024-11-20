#include "minishell.h"

static t_fd	*init_fd(t_data *data)
{
	t_fd	*fdstr;

	if (data->token_curr->next->type != WORD)
	{
		print_error("syntax error: invalid file name / delimiter", 2);
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
		fd->command->fdin = open(fd->filename, O_RDONLY);
	else
		fd->command->fdin = handle_heredoc_redirection(data);
	if (fd->command->fdin < 0)
		return (0);
	return (1);
}

static int	update_fdout(t_fd *fd)
{
	if (fd->command->fdout > 2)
		close(fd->command->fdout);
	if (fd->type == OUT)
		fd->command->fdout = open(fd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd->command->fdout = open(fd->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd->command->fdout < 0)
		return (0);
	return (1);
}

int	update_fd(t_data *data)
{
	t_fd	*fd;
	int		ret;

	fd = init_fd(data);
	if (fd == NULL)
	{
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
		print_error("Could not update fd", 2);
		free(data);
	}
	data->token_curr = data->token_curr->next;
	return (ret);
}
