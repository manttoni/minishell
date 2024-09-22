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

int		error_return(char *error_message);
void	free_split(char **s);
int		run_pipeline(char *input);
int		create_pipes(int *pipefds, int cmds);
void	close_pipes(int *pipefds, int cmds);
char	*extract_filename(char **command, char *redir);

#endif
