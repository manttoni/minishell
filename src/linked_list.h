#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>

typedef struct s_command
{
	t_command	*next;
	char		**args;
	char		*exe;
	int			fdin;
	int			fdout;
}	t_command;

#endif

