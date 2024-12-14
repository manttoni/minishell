/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:45:03 by amaula            #+#    #+#             */
/*   Updated: 2024/12/12 16:09:31 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	num_check(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (*s == 0)
		return (1);
	while (*(s + i))
	{
		if (*(s + i) >= '0' && *(s + i) <= '9')
		{
			i++;
			continue ;
		}
		else
			return (1);
	}
	return (0);
}

static void	print_too_many_args(t_command *list)
{
	while (list)
	{
		if (ft_strcmp(list->args[0], "exit") == 0)
		{
			if (len(list->args) > 2)
				print_error("-minishell: exit: too many arguments", 2);
			else if (len(list->args) == 2 && num_check(list->args[1]))
				print_error("-minishell: exit: numeric argument required", 2);
		}
		list = list->next;
	}
}

static int	run_exit(t_main *main_struct, int *ret)
{
	t_command	*last;

	last = last_command(main_struct->cmd_list);
	if (last->args == NULL || last->args[0] == NULL)
		return (0);
	print_too_many_args(main_struct->cmd_list);
	if (ft_strcmp(last->args[0], "exit") != 0)
		return (0);
	if (num_check(last->args[1]) == 1)
		*ret = 2;
	else if (len(last->args) > 1)
		*ret = ft_atoi(last->args[1]);
	if (list_len(main_struct->cmd_list) > 1)
		return (0);
	print_error("exit", 2);
	if (num_check(last->args[1]) == 1)
		return (1);
	if (len(last->args) > 2)
		return (0);
	if (last->args[1])
		*ret = ft_atoi(last->args[1]);
	return (1);
}

int	ft_exit(t_main *main_struct, int *ret)
{
	int	return_value;

	return_value = run_exit(main_struct, ret);
	main_struct->env->exit_code = *ret;
	if (return_value == 1)
		free_list(main_struct->cmd_list);
	return (return_value);
}
