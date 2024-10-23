#include "minishell.h"

t_command	*create_list(char *input, t_env *env)
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
		if (new == NULL)
		{
			printf("Error creating node\n");
			return (NULL);
		}
		add_node(&list, new);
		if (!ptr)
			break;
		input = ptr + 1;
	}
	return (list);
}

t_env	*init_env(char **arr)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->arr = malloc(sizeof(char *));
	if (env->arr == NULL)
		return (NULL);
	env->arr[0] = NULL;
	while (*arr)
	{
		env->arr = add(env->arr, *arr);
		arr++;
	}
	return (env);
}

int main(int argc, char **argv, char **env)
{
	char		*input;
	t_command	*list;
	t_env		*env_struct;

	if (argc != 1)
	{
		printf("Too many arguments\n");
		return (1);
	}
	(void) argv;
	env_struct = init_env(env);
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
			list = create_list(input, env_struct);
			if (list == NULL)
			{
				printf("create_list\n");
				continue ;
			}
			run(list, env_struct);
			free_list(list);
		}
		free(input);
	}
	return (0);
}
