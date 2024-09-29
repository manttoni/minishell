#include "minishell.h"

/* Like GNL, gets commands between pipes,
 * then moves the next command to input.
 * input is still freed in main */
char	*get_next_command(char *input)
{
	char	*cmd;
	char	*ptr;
	
	cmd = NULL;
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '\"')
		{
			ptr++;
			while (*ptr != '\"')
				ptr++;
		}
		else if (*ptr == '|' || *ptr == '\0')
			break ;
		ptr++;
	}
	cmd = ft_substring(input, 0, ptr - input);
	if (*ptr == '\0')
		ft_memset(input, 0, ft_strlen(input));
	else
		ft_memmove(ptr + 1, input, len(ptr + 1));
	return (cmd);
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
