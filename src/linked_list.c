#include "minishell.h"

// gets a command as char *cmd for example: command = "a | b | c" cmd would be a b or c
// redirection and filename/delimiter for << can be anywhere
t_command	*create_node(char *cmd, t_env *env)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	memset(command, 0, sizeof(t_command));
	if (parse_cmd(command, cmd, env) == 0)
	{
		printf("parse_cmd\n");
		return (NULL);
	}
	command->next = NULL;
	return (command);
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

void	add_node(t_command **list, t_command *new)
{
	t_command	*current;

	current = *list;
	new->index = list_len(current);
	if (current == NULL)
	{
		*list = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_node(t_command *node)
{
	free_array(node->args);
	free(node->exe);
	free(node);
}

void	free_list(t_command *list)
{
	if (list->next)
		free_list(list->next);
	free_node(list);
}
