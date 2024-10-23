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
# include "token.h"

typedef struct s_env
{
	char	**arr;
}	t_env;

t_token	*get_token(char *line);
void	free_token_list(t_token *token);
void	add_token_last(t_token **start, t_token *new);
char	*get_expandable(char *line);
int		len(char **ar);
char	**find(char **ar, char *str);
int		ft_remove(char **ar, char *str);
char	**add(char **ar, char *str);
char	*expand(char *string, t_env *env);
int		run_builtin(char **args, char **env);
int		parse_cmd(t_command *command, char *cmd, char **env);
int		error_return(char *error_message);
void	free_array(char **s);
int		run(t_command *list, char **env);

#endif
