#include "minishell.h"

t_env	*init_env(char **arr)
{
	t_env	*env;

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
	t_token	*tokens;

	if (argc != 1)
	{
		printf("Too many arguments (%d)\n", argc);
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
			if (unclosed_quotes(input))
				continue;
			tokens = tokenize_string(input, env_struct);
			list = create_list(tokens, env_struct);
			if (list == NULL)
			{
				free(input);
				free_array(env_struct->arr);
				free(env);
				free_token_list(tokens);
				return (1);
			}
			run(list, env_struct);
			printf("%d\n", env_struct->exit_code);
			free_list(list);
			free_token_list(tokens);
		}
		free(input);
		unlink(".here_doc");
	}
	return (0);
}
