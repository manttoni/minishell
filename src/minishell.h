/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:46:36 by amaula            #+#    #+#             */
/*   Updated: 2024/11/27 13:01:34 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

extern volatile sig_atomic_t	g_signal;

# define SUCCESS 0          // successful completion
# define ERR_STD 1          // standard error
# define ERR_EXEC 126       // execution failure
# define ERR_CMD_NOT_FOUND 127 // command not found

typedef struct s_exec_cmd
{
	char	*path_part;
	char	*executable;
}	t_exec_cmd;

/* struct for environment variables */
typedef struct s_env
{
	char	**arr;
	int		exit_code;
}	t_env;

/* a node for command-list */
typedef struct s_command
{
	struct s_command	*next;
	int					index;
	char				**args;
	int					fdin;
	int					fdout;
	char				*path;
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
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*string;
	struct s_token	*next;
}	t_token;

/* struct for variables in main */
typedef struct s_main
{
	t_env		*env;
	char		*input;
	t_command	*cmd_list;
	t_token		*tokens;
}	t_main;

/* struct for variables in run() */
typedef struct s_run
{
	t_env		*env;
	t_command	*cmd_list;
	t_command	*cmd_curr;
	pid_t		*pids;
	int			**pipefds;
	int			i;
	int			status;
	int			len;
	int			builtin;
}	t_run;

/* struct for variables in create_list() */
typedef struct s_data
{
	t_token		*token_list;
	t_token		*token_curr;
	t_env		*env;
	t_command	*cmd_list;
	t_command	*cmd_curr;
}	t_data;

/* struct for variables in update_fd */
typedef struct s_fd
{
	t_type		type;
	char		*filename;
	t_command	*command;
}	t_fd;

/* Builtins */
int			ft_export(char **args, t_env *env);
int			ft_unset(char **args, t_env *env);
int			ft_cd(char **args, t_env *env);
int			ft_env(t_command *cmd, t_env *env);
int			is_valid_key(char *key);
int			is_builtin(t_command *cmd, t_env *env);
int			get_builtin_type(t_run *run);

/* Process */
int			do_fork(t_run *run);
void		run_child(t_run *run);
void		wait_pids(t_run *run);

/* Command list */
t_command	*init_node(int i);
t_command	*create_list(t_token *tokens, t_env *env);
t_command	*last_command(t_command *list);
int			list_len(t_command *list);
int			update_fd(t_data *data);

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
int			run(t_main *main_struct);
int			wait_for_children(int num_processes);

/* Errors & validation */
int			unclosed_quotes(char *s);
char		*print_error(char *s, int n);

/* Memory */
void		free_array(char **s);
void		free_list(t_command *list);
void		free_token_list(t_token *token);
void		free_pipefds(int **pipefds, int len);
void		free_run(t_run *run);
void		free_data(t_fd *fd, t_data *data);

/* Utils */
int			len(char **ar);
char		**add(char **ar, char *str);
char		*join(char *freeable, char *suffix);
char		*find(char **ar, char *str);
void		ft_remove(char **ar, char *str);

/* Redirection / Pipes */
int			create_pipes(int **pipefds, int cmds);
void		close_pipes(int **pipefds, int cmds);
int			set_io(t_command *command, int **pipefds);
int			**allocate_pipefds(int len);

/* Heredoc */
int			handle_heredoc_redirection(t_fd	*fd, t_data *data);
void		setup_heredoc_signals(void);
int			interrupt_here_doc(char *eof, char *s, int *r_value, int i);

/* Signals */
void		setup_main_signals(void);
void		fork_sig_handler(int signum);
void		check_interrupt(t_main *main_struct);

#endif
