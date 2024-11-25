/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:06 by amaula            #+#    #+#             */
/*   Updated: 2024/11/21 11:23:26 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*init_data(t_token *tokens, t_env *env)
{
	t_data	*data;

	if (tokens == NULL)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->token_list = tokens;
	data->token_curr = tokens;
	data->env = env;
	data->cmd_list = init_node(0);
	if (data->cmd_list == NULL)
	{
		free(data);
		return (NULL);
	}
	data->cmd_curr = data->cmd_list;
	return (data);
}

static int	add_arg(t_data *data)
{
	data->cmd_curr->args = add(data->cmd_curr->args, data->token_curr->string);
	if (data->cmd_curr->args == NULL)
	{
		free_list(data->cmd_list);
		free(data);
		return (0);
	}
	return (1);
}

static int	add_command(t_data *data)
{
	if (data->token_curr == data->token_list)
	{
		print_error("syntax error: pipe first", 2);
		free_list(data->cmd_list);
		free(data);
		return (0);
	}
	if (data->token_curr->next == NULL)
	{
		print_error("syntax error: pipe last", 2);
		free_list(data->cmd_list);
		free(data);
		return (0);
	}
	data->cmd_curr->next = init_node(data->cmd_curr->index + 1);
	if (data->cmd_curr->next == NULL)
	{
		free_list(data->cmd_list);
		free(data);
		return (0);
	}
	data->cmd_curr = data->cmd_curr->next;
	return (1);
}

t_command	*create_list(t_token *tokens, t_env *env)
{
	t_data		*data;
	t_command	*list;

	data = init_data(tokens, env);
	if (data == NULL)
		return (NULL);
	while (data->token_curr)
	{
		if (data->token_curr->type == WORD)
		{
			if (add_arg(data) == 0)
				return (NULL);
		}
		else if (data->token_curr->type == PIPE)
		{
			if (add_command(data) == 0)
				return (NULL);
		}
		else if (update_fd(data) == 0)
			return (NULL);
		data->token_curr = data->token_curr->next;
	}
	list = data->cmd_list;
	free(data);
	return (list);
}
