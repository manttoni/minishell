#include "minishell.h"

t_command	*create_list(char *input)
{
	char		*cmd;
	t_command	*new;
	t_command	*list;

	list = NULL;
	cmd = get_next_command(input);
	while (cmd)
	{
		new = create_node(cmd);
		add_node(&list, new);
		cmd = get_next_command(input);
	}
	return (list);
}

int main(void)
{
	char		*input;
	t_command	*list;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		fflush(stdout);
		if (*input)
		{
			add_history(input);
			list = create_list(input);
			run(list);
			free_list(list);
		}
		free(input);
	}
	return (0);
}
