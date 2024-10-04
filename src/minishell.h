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

char	**cmd_split(char *cmd);
int		len(char **ar);
char	**find(char **ar, char *str);
int		ft_remove(char **ar, char *str);
char	**add(char **ar, char *str);
char	*ft_getenv(char	*key, char **env);
int		run_builtin(char **args, char **env);
int		parse_cmd(t_command *command, char *cmd, char **env);
int		error_return(char *error_message);
void	free_array(char **s);
int		run(t_command *list, char **env);
char	**extract_filein(char *cmd);
char	**extract_fileout(char *cmd);

#endif
