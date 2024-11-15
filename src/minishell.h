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

extern volatile sig_atomic_t g_signal;

#define SUCCESS 0          // successful completion
#define ERR_STD 1          // standard error
#define ERR_EXEC 126       // execution failure
#define ERR_CMD_NOT_FOUND 127 // command not found



typedef struct s_exec_cmd
{
	char	*path_part;
	char	*executable;
}	t_exec_cmd;

typedef struct s_env
{
	char	**arr;
	int		exit_code;
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

typedef struct s_data
{
	t_env *env;
	t_command	*start;
	t_token *tokens;
}	t_data;

/* Command list */
t_command	*init_node();
t_command	*create_list(t_token *tokens, t_env *env);
t_token		*tokenize_string(char	*cmd, t_env *env);
int			list_len(t_command *list);

/* Tokenizer */
t_token		*tokenize_string(char	*cmd, t_env *env);
t_token		*get_token(char *line);
void		remove_next_token(t_token *token);
void		add_token_last(t_token **start, t_token *new);

/* Environment (env) */
char		*get_expandable(char *line);
char		*expand(char *string, t_env *env);
char		*ft_getenv(char *key, t_env *env);
char		*find_path(t_command *cmd, t_env *env);

/* Execute */
int	run_builtin(char **args, t_env *env);
int	run(t_command *list, t_env *env);
int wait_for_children(int num_processes);

/* Errors & validation */
int		unclosed_quotes(char *s);
char	*print_error(char *s, int n);

/* Memory */
void		free_array(char **s);
void		free_list(t_command *list);
void		free_token_list(t_token *token);

/* Utils */
int			len(char **ar);
char		**add(char **ar, char *str);
char		*join(char *freeable, char *suffix);
char		*find(char **ar, char *str);
void		ft_remove(char **ar, char *str);


int handle_heredoc_redirection(t_token *token, t_env *env, t_data data);
void setup_heredoc_signals(void);
void setup_main_signals(void);
void reset_signals(void);
#endif
