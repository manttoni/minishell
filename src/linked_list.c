#include "minishell.h"

// gets a command as char *cmd for example: command = "a | b | c" cmd would be a b or c
// redirection and filename/delimiter for << can be anywhere
t_command	*create_node(char *cmd)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	memset(command, 0, sizeof(t_command));
	if (parse_cmd(command, cmd) == 0)
		return (error_return("parse_cmd"));
	command->next = NULL
	return (command);
}

void	add_node(t_command **list, t_command *new)
{
	t_command	*current;

	current = *list;
	if (current == NULL)
		*list = new;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_node(t_command *node)
{
	free_split(command->args);
	free(command->exe);
	free(node);
}

void	free_list(t_command *list)
{
	if (list->next)
		free_list(list->next);
	free_node(list);
	memset(list, 0, sizeof(t_command));
}
