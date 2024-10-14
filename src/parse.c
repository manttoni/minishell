/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:03:15 by mshabano          #+#    #+#             */
/*   Updated: 2024/10/14 15:33:33 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tokenize (t_ms *data)
{
	char *s = data->input;
	t_parsing p;

	ft_bzero(p, sizeof(t_parsing));
	while (*s)
	{
		while (*s)
		{
			s = skip_spaces(s);
			p.meta_start = s;
			while (!ft_strchr(META, *s) && *s)
				s++;
			p->meta_end = s;
			
				
		}
	}
}

void split_to_tokens (t_ms *data)
{
	if (tokenize(data))
		return (print_error("Memory allocation failed in tokenize()");
	if (expand(data))
		return (print_error("Memory allocation failed in expand1()");
}

void parse(t_ms &data)
{
	if (unclosed_quotes(data->input))
		return (print_error("Unclosed quotes foud in the prompt\n", 0);
	split_to_tokens(data);
}
