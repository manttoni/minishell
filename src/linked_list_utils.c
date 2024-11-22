/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:19 by amaula            #+#    #+#             */
/*   Updated: 2024/11/22 12:19:11 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*last_command(t_command *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	free_list(t_command *list)
{
	if (list->next)
		free_list(list->next);
	free_array(list->args);
	free(list->path);
	free(list);
}

t_command	*init_node(int i)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_command));
	node->fdout = 1;
	node->args = malloc(sizeof(char *));
	if (node->args == NULL)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = NULL;
	node->index = i;
	return (node);
}

int	list_len(t_command *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}
