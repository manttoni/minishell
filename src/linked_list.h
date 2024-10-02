#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>

typedef struct s_command
{
	struct s_command	*next;
	int					index;
	char				**args;
	char				*exe;
	int					fdin;
	int					fdout;
}	t_command;

int			list_len(t_command *list);
void		free_list(t_command *list);
t_command	*create_node(char *cmd, char **env);
void		add_node(t_command **list, t_command *command);

#endif

