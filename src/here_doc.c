#include "minishell.h"

static void	expand_heredoc(char *line, int fd, t_env *env)
{
	char	*expanded;

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
int	process_heredoc_input(t_data *data)
{
	char	*line;
	int		r_value;
	int		fd;

	r_value = 1;
	setup_heredoc_signals();
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	while (42)
	{
		line = readline("> ");
		if (g_signal == 2)
		{
			r_value = 130;
			break ;
		}
		if (!line)
		{
			unexpected_eof(ft_itoa(42), data->token_curr->next->string);
			break ;
		}
		if (!ft_strcmp(line, data->token_curr->next->string))
		{
			free(line);
			break ;
		}
		expand_heredoc(line, fd, data->env);
	}
	close(fd);
	return(r_value);
}

int	handle_heredoc_redirection(t_data *data)
{
	signal(SIGINT, SIG_IGN);
	process_heredoc_input(data);
	g_signal = 0;
	return (open(".here_doc", O_RDONLY));
}
