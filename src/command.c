#include "minishell.h"

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

int	set_io(t_command *command, int *pipefds)
{
	if (command->fdin != 0) // command gets input from file
		dup2(command->fdin, STDIN_FILENO);
	else if (command->index != 0) // command is not the first one
		dup2(pipefds[2 * (command->index - 1)], STDIN_FILENO);
	if (command->fdout != 1) // command outputs into file
		dup2(command->fdout, STDOUT_FILENO);
	else if (list_len(command) != 1) //command is not the last one
		dup2(pipefds[2 * command->index + 1], STDOUT_FILENO);
	close(command->fdin);
	close(command->fdout);
	return (1);
}


int	run(t_command *list)
{
	printf("test\n");
	t_command	*current;
	int			id;
	int			pipefds[2 * (list_len(list) - 1)];

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
			printf("Command: \n\texe: %s\n\targs[0]:%s\n", current->exe, current->args[0]);
			execve(current->exe, current->args, NULL);
			free_list(list);
			return (error_return("execve"));
		}
		wait(NULL);
		current = current->next;
	}
	close_pipes(pipefds, list_len(list));
	return (1);
}
