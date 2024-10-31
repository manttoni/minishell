#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
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

typedef struct s_exec_cmd
{
	char	*path_part;
	char	*executable;
}	t_exec_cmd;

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
	char	*path;
}	t_command;

typedef enum type
{
	SPACE_TOKEN,
	SINGLE,
	DOUBLE,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	WORD,
	EXPANDABLE
}       e_type;

typedef struct s_token
{
        e_type  type;
        char    *string;
        struct s_token  *next;
}       t_token;

t_command	*init_node();
t_command	*create_list(t_token *tokens, t_env *env);
t_token		*tokenize_string(char	*cmd, t_env *env);
int			list_len(t_command *list);
void		free_list(t_command *list);
t_token		*get_token(char *line);
void		free_token_list(t_token *token);
void		remove_next_token(t_token *token);
void		add_token_last(t_token **start, t_token *new);
char		*get_expandable(char *line);
int			len(char **ar);
char		**add(char **ar, char *str);
char		*expand(char *string, t_env *env);
int			run_builtin(char **args, t_env *env);
int			error_return(char *error_message);
void		free_array(char **s);
int			run(t_command *list, t_env *env);
char		*ft_getenv(char *key, t_env *env);
char		*join(char *freeable, char *suffix);
int     unclosed_quotes(char *s);
char *find_path(t_command *cmd, t_env *env);
char *print_error(char *s, int n);
int handle_heredoc_redirection(t_token *token, t_env *env);
#endif
