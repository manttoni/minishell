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
		env->arr = add(env->arr, *arr);
		arr++;
	}
	return (env);
}
int main(int argc, char **argv, char **env)
{
    char        *input;
    t_command    *list;
    t_env        *env_struct;
    t_token    *tokens;

    setup_main_signals();
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
            break;
        fflush(stdout);
        if (*input)
        {
            add_history(input);
            if (unclosed_quotes(input))
            {
                free(input);
                continue;
            }
            tokens = tokenize_string(input, env_struct);
            list = create_list(tokens, env_struct);
            if (list == NULL)
            {
                free(input);
                free_token_list(tokens);
                continue;
            }
            run(list, env_struct);
            free_list(list);
            free_token_list(tokens);
        }
        free(input);
        unlink(".here_doc");
    }
    return (0);
}
