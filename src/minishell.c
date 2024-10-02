#include "minishell.h"

t_command	*create_list(char *input, char **env)
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
			new = create_node(ft_substr(input, 0, ptr - input), env);
		else
			new = create_node(ft_strdup(input), env);
		add_node(&list, new);
		if (!ptr)
			break;
		input = ptr + 1;
	}
	return (list);
}

char	**copy_array(char **ar)
{
	char	**env;
	int		i;

	env = malloc((len(ar) + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (ar[i])
	{
		env[i] = ft_strdup(ar[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
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
	env = copy_array(env);
	if (env == NULL)
		return (1);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		fflush(stdout);
		if (*input)
		{
			add_history(input);
			list = create_list(input, env);
			if (list == NULL)
			{
				printf("create_list\n");
				return (1);
			}
			run(list, env);
			free_list(list);
		}
		free(input);
	}
	return (0);
}
