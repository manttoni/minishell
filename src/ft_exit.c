/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:45:03 by amaula            #+#    #+#             */
/*   Updated: 2024/12/12 15:07:41 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_too_many_args(t_command *list)
{
	while (list)
	{
		if (ft_strcmp(list->args[0], "exit") == 0)
			if (len(list->args) > 2)
				print_error("-minishell: exit: too many arguments", 2);
		list = list->next;
	}
}

int	ft_exit(t_main main_struct, int *ret)
{
	t_command	*last;

	print_too_many_args(main_struct.cmd_list);
	last = last_command(main_struct.cmd_list);
	if (ft_strcmp(last->args[0], "exit") != 0)
		return (0);
	print_error("exit", 2);
	if (len(last->args) > 2)
		return (0);
	if (last->args[1])
		*ret = ft_atoi(last->args[1]);
	return (1);
}
