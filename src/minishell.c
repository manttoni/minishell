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
		env->arr = add(env->arr, ft_strdup(*arr));
		arr++;
	}
	return (env);
}

int main(int argc, char **argv, char **env)
{
	char		*input;
	t_command	*list;
	t_env		*env_struct;
	t_token		*tokens;

	if (argc != 1)
	{
		printf("Too many arguments (%d)\n", argc);
		return (1);
	}
	(void) argv;
	env_struct = init_env(env);
	if (env == NULL)
		return (1);
	input = NULL;
	while (1)
	{
		input = readline("minishell> ");
		
		if (input == NULL)
			break ;
		fflush(stdout); // was this useless?
		if (*input)
		{
			add_history(input);
			if (unclosed_quotes(input))
				continue;
			tokens = tokenize_string(input, env_struct);
			list = create_list(tokens, env_struct);
			free_token_list(tokens);
			if (list == NULL)
			{
				free(input);
				free_array(env_struct->arr);
				free(env);
				return (1);
			}
			run(list, env_struct);
			free_list(list);
		}
		free(input);
		unlink(".here_doc");
	}
	free_array(env_struct->arr);
	free(env_struct);
	clear_history();
	return (0);
}
