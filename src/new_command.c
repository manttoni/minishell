#include "minishell.h"

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

int	run(t_command *list)
{
	t_command	*current;
	int			id;

	current = list;
	while (current)
	{
		if = fork();
		if (id == -1)
			return (error_return("fork"));
		if (if == 0)
		{
			execve(current->exe, current->args, NULL);
			free_list(list);
			return (error_return("execve"));
		}
		wait(NULL);
		current = current->next;
	}
	return (1);
}
