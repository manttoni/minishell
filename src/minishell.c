#include "minishell.h"

t_command	*create_list(char *input)
{
	char		*ptr;
	t_command	*new;
	t_command	*list;

	list = NULL;
	ptr = input;
	while (*input)
	{
		ptr = ft_strchr(input, '|');
		if (ptr)
			new = create_node(ft_substr(input, 0, ptr - input));
		else
			new = create_node(ft_strdup(input));
		add_node(&list, new);
		if (!ptr)
			break;
		input = ptr + 1;
	}
	return (list);
}

int main(int argc, char **argv, char **env)
{
	char		*input;
	t_command	*list;

	if (argc != 1)
	{
		printf("Too many arguments\n");
		return (1);
	}
	(void) argv;
	init_env(env);
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
			if (list == NULL)
			{
				printf("create_list\n");
				return (1);
			}
			run(list);
			free_list(list);
		}
		free(input);
	}
	return (0);
}
