/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:35:15 by amaula            #+#    #+#             */
/*   Updated: 2024/10/18 16:39:12 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

# define SINGLE 1
# define DOUBLE 2
# define PIPE 3
# define IN 5
# define OUT 6
# define HEREDOC 7
# define APPEND 8
# define WORD 9

typedef struct s_token
{
	int	type;
	char	*string;
	struct s_token	*next;
}	t_token;

#endif
