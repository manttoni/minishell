#include "minishell.h"

int	create_pipes(int pipefds[][2], int cmds)
{
	int	i;

	i = 0;
	while (i < cmds - 1)
	{
		if (pipe(pipefds[i]) == -1)
			return (error_return("pipe"));
		i++;
	}
	return (1);
}

void	close_pipes(int pipefds[][2], int cmds)
{
	int	i;

	i = 0;
	while (i < cmds - 1)
	{
		close(pipefds[i][1]);
		close(pipefds[i][0]);
		i++;
	}
}

int	set_io(t_command *command, int pipefds[][2])
{
	if (command->fdin != 0) // command gets input from file
		dup2(command->fdin, STDIN_FILENO);
	else if (command->index != 0) // command is not the first one
		dup2(pipefds[command->index - 1][0], STDIN_FILENO);
	if (command->fdout != 1) // command outputs into file
		dup2(command->fdout, STDOUT_FILENO);
	else if (list_len(command) != 1) //command is not the last one
		dup2(pipefds[command->index][1], STDOUT_FILENO);
	if (command->fdin > 1)
		close(command->fdin);
	if (command->fdout > 1)
		close(command->fdout);
	return (1);
}

char	*exitchar(int asd)
{
	char	*itoa;
	char	*ret;

	itoa = ft_itoa(asd);
	ret = ft_strjoin("?=", itoa);
	free(itoa);
	return (ret);
}

int	run(t_command *list, char **env)
{
	t_command	*current;
	int			id;
	int			pipefds[list_len(list)][2];

	if (ft_strcmp("cd", list->args[0]) == 0 || ft_strcmp("export", list->args[0]) == 0 || ft_strcmp("unset", list->args[0]) == 0)
	{
		run_builtin(list->args, env);
		return (1);
	}
	if (create_pipes(pipefds, list_len(list)) == 0)
		return (error_return("create_pipes"));
	current = list;
	while (current)
	{
		id = fork();
		if (id == -1)
			return (error_return("fork"));
		if (id == 0)
		{
			set_io(current, pipefds);
			close_pipes(pipefds, list_len(list));
			execve(current->exe, current->args, NULL);
			free_list(list);
			return (error_return("execve"));
		}
		current = current->next;
	}
	close_pipes(pipefds, list_len(list));
	int asd;
	for (int i = 0; i < list_len(list); ++i)
	{
		wait(&asd);
	}
	env = add(env, exitchar(asd));
	return (asd);
}
