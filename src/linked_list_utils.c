#include "minishell.h"

void	free_list(t_command *list)
{
	if (list->next)
		free_list(list->next);
	free_array(list->args);
	free(list->exe);
	if (list->fdin > 2)
		close(list->fdin);
	if (list->fdout > 2)
		close(list->fdout);
	free(list);
}

t_command	*init_node(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_command));
	node->fdout = 1;
	node->args = malloc(sizeof(char *));
	if (node->args == NULL)
		return (NULL);
	node->args[0] = NULL;
	return node;
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
