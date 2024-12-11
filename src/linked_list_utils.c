/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:19 by amaula            #+#    #+#             */
/*   Updated: 2024/12/03 21:08:07 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*last_command(t_command *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	free_list(t_command *list)
{
	if (list == NULL)
		return (1);
	if (list->next)
		free_list(list->next);
	if (list->fdin > 2)
		close(list->fdin);
	if (list->fdout > 2)
		close(list->fdout);
	free_array(list->args);
	free(list->path);
	free(list);
	return (1);
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
