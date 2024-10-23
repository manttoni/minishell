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
# include "token.h"

typedef struct s_env
{
	char	**arr;
}	t_env;

typedef struct s_command
{
	struct s_command	*next;
	int					index;
	char				**args;
	char				*exe;
	int					fdin;
	int					fdout;
}	t_command;

t_token	*tokenize_string(char	*cmd, t_env *env);
int			list_len(t_command *list);
void		free_list(t_command *list);
t_command	*create_node(char *cmd, t_env *env);
void		add_node(t_command **list, t_command *command);
t_token	*get_token(char *line);
void	free_token_list(t_token *token);
void	add_token_last(t_token **start, t_token *new);
char	*get_expandable(char *line);
int		len(char **ar);
char	**find(char **ar, char *str);
int		ft_remove(char **ar, char *str);
char	**add(char **ar, char *str);
char	*expand(char *string, t_env *env);
int		run_builtin(char **args, t_env *env);
int		parse_cmd(t_command *command, char *cmd, t_env *env);
int		error_return(char *error_message);
void	free_array(char **s);
int		run(t_command *list, t_env *env);
char	*ft_getenv(char *key, t_env *env);

#endif
