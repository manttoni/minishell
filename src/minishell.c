#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

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

/* For norminette */
static t_main	*init_main(int argc, char **argv, char **env)
{
	t_main	*main_struct;

	if (argc != 1)
		return (NULL);
	main_struct = malloc(sizeof(t_main));
	if (main_struct == NULL)
		return (NULL);
	main_struct->env = init_env(env);
	if (main_struct->env == NULL)
	{
		free(main_struct);
		return (NULL);
	}
	(void) argv;
	return (main_struct);
}

/* Return values:
 * 	- 0: everything ok
 * 	- 1: main should break, input == NULL
*/
static int	handle_input(t_main *main_struct)
{
	setup_main_signals();
	main_struct->input = readline("minishell> ");
	if (main_struct->input == NULL)
		return (1);
	add_history(main_struct->input);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_main	*main_s;

	main_s = init_main(argc, argv, env);
	if (main_s == NULL)
		return (1);
	while (1)
	{
		if (handle_input(main_s) == 1)
			break ;
		if (unclosed_quotes(main_s->input))
			continue ;
		main_s->tokens = tokenize_string(main_s->input, main_s->env);
		main_s->commands = create_list(main_s->tokens, main_s->env);
		free(main_s->input);
		free_token_list(main_s->tokens);
		if (main_s->commands == NULL)
			continue ;
		run(main_s->commands, main_s->env);
		free_list(main_s->commands);
		unlink(".here_doc");
	}
	free_array(main_s->env->arr);
	free(main_s->env);
	clear_history();
	return (0);
}
