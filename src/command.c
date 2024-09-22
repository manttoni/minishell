#include "minishell.h"

/* Like GNL, gets commands between pipes,
 * then moves the next command to input.
 * input is still freed in main */
char	**get_next_command(char *input)
{
	char	**command;
	char	*sub;
	int		cmd_len;
	char	*pipe;
	
	if (*input == '\0')
		return (NULL);
	pipe = ft_strchr(input, '|');
	if (pipe == NULL)
	{
		command = ft_split(input, ' ');
		ft_bzero(input, ft_strlen(input));
		return (command);
	}
	cmd_len = pipe - input;
	sub = ft_substr(input, 0, cmd_len);
	command = ft_split(sub, ' ');
	ft_memmove(input, pipe + 1, ft_strlen(input) - cmd_len + 1);
	free(sub);
	return (command);
}

int	count_commands(char *input)
{
	int	cmds;
	
	cmds = 1;
	while (ft_strchr(input, '|'))
	{
		cmds++;
		input = ft_strchr(input, '|') + 1;
	}
	return (cmds);
}

int	run_command(char **cmd, char *exe)
{
	execve(exe, cmd, NULL);
	return (error_return("execve"));
}

int	create_pipes(int *pipefds, int cmds)
{
	int	i;

	i = 0;
	while (i < cmds - 1)
	{
		if (pipe(pipefds + 2 * i) == -1)
			return (error_return("pipe"));
		i++;
	}
	return (1);
}

void	close_pipes(int *pipefds, int cmds)
{
	int	i;

	i = 0;
	while (i < 2 * (cmds - 1))
	{
		close(pipefds[i]);
		i++;
	}
}

int	run_pipeline(char *input)
{
	int		cmds;
	int		i;
	int		pipefds[2 * (count_commands(input) - 1)];
	int		id;
	char	**command;
	char	*exe;

	cmds = count_commands(input);
	if (create_pipes(pipefds, cmds) == 0)
		return (error_return("create_pipes"));
	i = 0;
	while (i < cmds)
	{
		id = fork();
		if (id == -1)
			return (error_return("fork"));
		command = get_next_command(input);
		exe = ft_strjoin("/bin/", command[0]);
		if (id == 0)
		{
			if (i > 0)
				dup2(pipefds[2 * (i - 1)], STDIN_FILENO);
			if (i < cmds - 1)
				dup2(pipefds[2 * i + 1], STDOUT_FILENO);
			close_pipes(pipefds, cmds);
			run_command(command, exe);
			free(exe);
			free_split(command);
			return(error_return("run_command"));
		}
		free(exe);
		free_split(command);
		i++;
	}
	close_pipes(pipefds, cmds);
	i = 0;
	while (i < cmds)
	{
		wait(NULL);
		i++;
	}
	return (1);
}
