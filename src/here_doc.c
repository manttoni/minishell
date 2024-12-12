/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:04:40 by mshabano          #+#    #+#             */
/*   Updated: 2024/12/09 09:36:25 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_heredoc(char *line, int fd, t_env *env)
{
	char	*expanded;

	if (!line || fd < 0)
		return ;
	expanded = expand(line, env);
	if (expanded)
	{
		ft_putendl_fd(expanded, fd);
		free(expanded);
	}
}

void	free_data(t_fd *fd, t_data *data)
{
	if (data->env)
	{
		free_array(data->env->arr);
		free(data->env);
	}
	if (data->cmd_list)
		free_list(data->cmd_list);
	if (data->token_list)
		free_token_list(data->token_list);
	if (data)
		free(data);
	if (fd)
		free(fd);
}

int	init_heredoc( int *fd, int *r_value)
{
	if (setup_signals(HEREDOC_SIG))
		return (1);
	*fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	*r_value = 0;
	if (*fd == -1)
	{
		print_error(".here_doc cannot be opened", 0);
		return (1);
	}
	return (0);
}

int	process_heredoc_input(char *eof, t_fd *fds, t_data *data)
{
	int		fd;
	char	*s;
	int		i;
	int		r_value;

	if (init_heredoc(&fd, &r_value))
		r_value = 1;
	else
	{
		i = 0;
		while (42)
		{
			s = readline("> ");
			if (interrupt_here_doc(eof, s, &r_value, i))
				break ;
			expand_heredoc(s, fd, data->env);
			i++;
		}
		if (close(fd) == -1)
			print_error("unable to close here_doc fd", 0);
	}
	free_data(fds, data);
	exit(r_value);
}

int	handle_heredoc_redirection(t_fd	*fd, t_data *data)
{
	pid_t	pid;
	int		status;
	int		code;

	code = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		print_error("fork failed to execute", 0);
		exit(1);
	}
	else if (!pid)
		process_heredoc_input(data->token_curr->next->string, fd, data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	if (code)
	{
		data->env->exit_code = code;
		g_signal = 0;
		return (-1);
	}
	else
		return (open(".here_doc", O_RDONLY));
}
