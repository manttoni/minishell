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

void	unexpected_eof(char *i, char *eof)
{
	if (!i)
		i = "0";
	ft_putstr_fd("-minishell: warning: here-document at line ", 2);
	ft_putstr_fd(i, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
	free(i);
}

int interrupt_here_doc(char *eof, char *s, int *r_value, int i)
{
	if (g_signal == 2)
	{
		*r_value = 130;
		return (1) ;
	}
	if (!s)
	{
		unexpected_eof(ft_itoa(i), eof);
		return (1);
	}
	if (!ft_strcmp(s, eof))
	{
		free(s);
		return (1);
	}
	return (0);
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


int	process_heredoc_input(char *eof, t_fd *fds, t_data *data)
{
	int		fd;
	char	*s;
	int		i;
	int		r_value;

	setup_heredoc_signals();
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	r_value = 0;
	if (fd == -1)
	{
		print_error(".here_doc cannot be opened", 0);
		r_value = 1;
	}
	else
	{
		i = 0;
		while (42)
		{
			s = readline("> ");
			if (interrupt_here_doc(eof, s, &r_value, i))
				break;
			expand_heredoc(s, fd, data->env);
			i++;
		}
		close(fd);
	}
	free_data(fds, data);
	exit(r_value);
}

int	handle_heredoc_redirection(t_fd	*fd, t_data *data)
{
	pid_t	pid;
	char	*eof;
	int		status;
	int		code;

	signal(SIGINT, SIG_IGN);
	eof = data->token_curr->next->string;
	pid = fork();
	if (pid < 0)
		exit(printf("fork has failed"));
	else if (!pid)
		process_heredoc_input(eof, fd, data);
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