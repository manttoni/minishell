/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:35:51 by amaula            #+#    #+#             */
/*   Updated: 2024/12/05 07:52:40 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

t_env	*init_env(char **arr)
{
	t_env	*env;
	char	**buf;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->arr = ft_calloc(1, sizeof(char *));
	if (env->arr == NULL)
		return (free_env(env));
	while (*arr)
	{
		env->arr = add(env->arr, *arr);
		if (env->arr == NULL)
			return (free_env(env));
		arr++;
	}
	buf = ft_calloc(3, sizeof(char *));
	if (buf == NULL)
		return (free_env(env));
	buf[0] = "_";
	buf[1] = "SHLVL";
	ft_unset(buf, env);
	free(buf);
	env->exit_code = 0;
	return (env);
}

/* For norminette */
static int	init_main(int argc, char **argv, char **env, t_main *main_struct)
{
	if (argc > 1)
	{
		print_error("too many arguments\n", 0);
		return (1);
	}
	main_struct->env = init_env(env);
	if (main_struct->env == NULL)
		return (1);
	(void) argv;
	return (0);
}

/*
 * Return values:
 * 	- 0: everything ok
 * 	- 1: main should break, input == NULL
*/
static int	handle_input(t_main *main_s)
{
	setup_main_signals();
	main_s->input = readline("minishell> ");
	if (main_s->input == NULL)
		return (1);
	add_history(main_s->input);
	return (0);
}

static void	free_main(t_main *main_struct)
{
	free_array(main_struct->env->arr);
	free(main_struct->env);
}

int	main(int argc, char **argv, char **env)
{
	t_main	main_s;

	if (init_main(argc, argv, env, &main_s))
		return (1);
	while (1)
	{
		if (handle_input(&main_s) == 1)
			break ;
		if (unclosed_quotes(main_s.input))
			continue ;
		main_s.tokens = tokenize_string(main_s.input, main_s.env);
		main_s.cmd_list = create_list(main_s.tokens, main_s.env);
		free(main_s.input);
		free_token_list(main_s.tokens);
		if (main_s.cmd_list == NULL)
			continue ;
		if (run(&main_s) == 0)
			break ;
		unlink(".here_doc");
	}
	free_main(&main_s);
	clear_history();
	return (0);
}
