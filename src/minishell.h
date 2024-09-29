#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "../lib/libft/libft.h"
# include "linked_list.h"

int		parse_cmd(t_command *command, char *cmd);
int		error_return(char *error_message);
void	free_split(char **s);
int		run(t_command *list);
int		create_pipes(int *pipefds, int cmds);
void	close_pipes(int *pipefds, int cmds);
char	**extract_filein(char *cmd);
char	**extract_fileout(char *cmd);

#endif
