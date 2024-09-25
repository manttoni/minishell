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

int	set_io(char **command, int *pipefds, int i, int cmds)
{
	char	*file_in;
	char	*file_out;
	int		fdin;
	int		fdout;

	file_in = extract_filename(command, "<");
	file_out = extract_filename(command, ">");
	if (file_in != NULL)
	{
		fdin = open(file_in, O_RDONLY);
		if (fdin < 0)
		{
			free(file_in);
			return (error_return("open fdin"));
		}
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	else if (i > 0)
		dup2(pipefds[2 * (i - 1)], STDIN_FILENO);
	if (file_out != NULL)
	{
		fdout = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fdout < 0)
		{
			if (fdin >= 0)
				close(fdin);
			free(file_out);
			return (error_return("open fdout"));
		}
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	else if (i < cmds - 1)
		dup2(pipefds[2 * i + 1], STDOUT_FILENO);
	close_pipes(pipefds, cmds);
	free(file_in);
	free(file_out);
	return (1);
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
			if (set_io(command, pipefds, i, cmds) == 0)
				return (error_return("set_io"));
			ignore_redirs(command);
			execve(exe, command, NULL);
			free(exe);
			free_split(command);
			return(error_return("execve"));
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
