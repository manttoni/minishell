#include "minishell.h"

e_type	get_type(char *line)
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
	while (ft_isalnum(*end) || *end == '_')
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
		return (ft_substr(line, 1, ft_strchr(line + 1, '\'') - 1 - line)); // quotes are trimmed here
	if (token->type == DOUBLE)
		return (ft_substr(line, 1, ft_strchr(line + 1, '\"') - 1 - line)); // and here
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
		free(token->string);
		free(token->next);
		free(token);
		return (NULL);
	}
	return (token);
}
