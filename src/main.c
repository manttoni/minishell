/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:27:05 by mshabano          #+#    #+#             */
/*   Updated: 2024/10/14 15:33:32 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_minishell(int ac, char **av, char **env, t_ms *data)
{
	ft_bzero(data, sizeof(t_ms));
	if (ac != 1)
	{
		print_error("Too many args\n", 0);
		return (1);
	}
	(void)av;
	data->env = copy_array(env);
	if (!data.env)
		print_error("Unable to copy env", 0);
}

int main(int ac, char **av, char **env)
{
	t_ms data;
	
	init_minishell(ac, av, env, &data);
	while(1)
	{
		data.input = readline("minishell> ");
		if (data.input == 0)
			continue;
		fflush(stdout);
		add_history(data.input);
		parse(&data);
		if (!data.tokens)
			continue;
		execute(&data);
	}
}	
