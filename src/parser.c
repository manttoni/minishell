#include "minishell.h"

int	heredoc(char *delimiter)
{
	int		fd;
	char	*input;

	printf("Delimiter: %s\n", delimiter);
	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	input = "";
	while (1)
	{
		input = readline("heredoc> ");
		fflush(stdout);
		if (ft_strcmp(input, delimiter) == 0)
			break ;
		write(fd, input, ft_strlen(input));
	}
	close(fd);
	return (open(".tmp", O_RDONLY));
}

int	set_fdin(t_command *command, char *cmd)
{
	char	**file_in;

	file_in = extract_filein(cmd); //returns info of last redirection
	if (file_in)
	{
		if (ft_strncmp(file_in[1], "<", 2) == 0)
			command->fdin = open(file_in[0], O_RDONLY);
		else if (ft_strncmp(file_in[1], "<<", 2) == 0)
			command->fdin = heredoc(file_in[0]); // give delimiter
		if (command->fdin < 0)
		{
			return (error_return("opening file in"));
		}
	}
	else
		command->fdin = 0;
	return (1);
}

int	set_fdout(t_command *command, char *cmd)
{
	char	**file_out;

	file_out = extract_fileout(cmd); //returns info of last redirection
	if (file_out)
	{
		if (ft_strncmp(file_out[1], ">", 2) == 0)
			command->fdout = open(file_out[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strncmp(file_out[1], ">>", 2) == 0)
			command->fdout = open(file_out[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (command->fdout < 0)
		{
			if (command->fdin >= 0)
				close(command->fdin);
			return (error_return("opening file out"));
		}
	}
	else
		command->fdout = 1;
	return (1);
}

int	set_args(t_command *command, char *cmd)
{
	int		space;
	char	*ptr;

	ptr = cmd;
	while (*cmd)
	{
		if (ft_strchr("<>", *cmd))
		{
			space = 0;
			if (*(cmd + 1) == ' ' || *(cmd + 2) == ' ')
				space = 1;
			while (*cmd && (*cmd != ' ' || space == 1))
			{
				if (*cmd == ' ' && space == 1)
					space = 0;
				*cmd = ' ';
				cmd++;
			}
		}
		if (*cmd)
			cmd++;
	}
	command->args = ft_split(ptr, ' ');
	return (1);
}

void	expand(char **args, int i)
{
	char	*value;

	value = getenv(args[i] + 1);
	free(args[i]);
	if (value != NULL)
	{
		args[i] = value;
		return ;
	}
	while (args[i])
	{
		args[i] = args[i+1];
		i++;
	}
}
	

int	replace_env_vars(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
			expand(args, i);
		i++;
	}
	return (1);
}

int	parse_cmd(t_command *command, char *cmd)
{
	if (set_fdin(command, cmd) == 0)
		return (error_return("set_fdin"));
	if (set_fdout(command, cmd) == 0)
		return (error_return("set_fdout"));
	if (set_args(command, cmd) == 0)
		return (error_return("set_args"));
	if (replace_env_vars(command->args) == 0)
		return (error_return("replace_env_vars"));
	command->exe = ft_strjoin("/bin/", command->args[0]);
	return (1);
}
