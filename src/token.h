/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:37:31 by mshabano          #+#    #+#             */
/*   Updated: 2024/10/14 15:37:25 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# ifndef META
#  define META "\"'<>$| \t\n"


# include "minishell.h"
# include <bool.h>
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


typedef struct s_parsing	{
	char *meta_start;
	char *meta_end;
	char *token_start;
	char *token_end;
} t_parsing;

typedef enum e_t_type	{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EXPAND
}	t_t_type;

typedef struct s_node	{
	t_t_type	type;
	int		index;
	char		*value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct ms {
	char *input;
	t_node *tokens;
	int tokens_length;
	char **env;
}	t_ms;
