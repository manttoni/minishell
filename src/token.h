/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:35:15 by amaula            #+#    #+#             */
/*   Updated: 2024/10/18 17:32:31 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef enum type
{
	SINGLE,
	DOUBLE,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	WORD,
	EXPANDABLE
}	e_type;

typedef struct s_token
{
	e_type	type;
	char	*string;
	struct s_token	*next;
}	t_token;

#endif
