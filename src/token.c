/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:35:17 by amaula            #+#    #+#             */
/*   Updated: 2024/11/22 12:13:16 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_type(char *line)
{
	if (*line == ' ')
		return (SPACE_TOKEN);
	if (*line == '$')
		return (EXPANDABLE);
	if (*line == '\'')
		return (SINGLE);
	if (*line == '\"')
		return (DOUBLE);
	if (*line == '|')
		return (PIPE);
	if (ft_strncmp("<<", line, 2) == 0)
		return (HEREDOC);
	else if (*line == '<')
		return (IN);
	if (ft_strncmp(">>", line, 2) == 0)
		return (APPEND);
	else if (*line == '>')
		return (OUT);
	return (WORD);
}

/* returns an EXPANDABLE tokens string.
 * it includes always the first $ and
 * the next char no matter what it is.
 * Rest of chars have to be alphanum or _ */
char	*get_expandable(char *line)
{
	char	*end;

	end = line + 2;
	while ((ft_isalpha(*(line + 1)) || *(line + 1) == '_')
		&& (ft_isalnum(*end) || *end == '_'))
		end++;
	return (ft_substr(line, 0, end - line));
}

char	*get_word(char *line)
{
	char	*ptr;
	char	*word_end;

	ptr = line;
	word_end = "|<>\"\'$ ";
	while (*ptr && ft_strchr(word_end, *ptr) == NULL)
		ptr++;
	return (ft_substr(line, 0, ptr - line));
}

char	*get_string(t_token *token, char *line)
{
	if (token->type == SPACE_TOKEN)
		return (ft_strdup(" "));
	if (token->type == SINGLE)
		return (ft_substr(line, 1, ft_strchr(line + 1, '\'') - 1 - line));
	if (token->type == DOUBLE)
		return (ft_substr(line, 1, ft_strchr(line + 1, '\"') - 1 - line));
	if (token->type == PIPE)
		return (ft_strdup("|"));
	if (token->type == HEREDOC)
		return (ft_strdup("<<"));
	if (token->type == IN)
		return (ft_strdup("<"));
	if (token->type == APPEND)
		return (ft_strdup(">>"));
	if (token->type == OUT)
		return (ft_strdup(">"));
	if (token->type == EXPANDABLE)
		return (get_expandable(line));
	return (get_word(line));
}

t_token	*get_token(char *line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = get_type(line);
	token->string = get_string(token, line);
	token->next = NULL;
	if (!token->string)
	{
		free(token);
		return (NULL);
	}
	return (token);
}
