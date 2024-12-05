/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:48:11 by amaula            #+#    #+#             */
/*   Updated: 2024/12/05 08:05:30 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*type_to_string(t_type type)
{
	switch (type)
	{
		case SPACE_TOKEN:
			return ("SPACE");
		case SINGLE:
			return ("SINGLE");
		case DOUBLE:
			return ("DOUBLE");
		case PIPE:
			return ("PIPE");
		case IN:
			return ("IN");
		case OUT:
			return ("OUT");
		case HEREDOC:
			return ("HEREDOC");
		case APPEND:
			return ("APPEND");
		case WORD:
			return ("WORD");
		case EXPANDABLE:
			return ("EXPANDABLE");
		default:
			return ("UNKNOWN");
	}
}

void	print_token(t_token *token)
{
	if (token == NULL)
		printf("List is empty\n");
	while (token)
	{
		printf("type=%s string=%s\n",
		...type_to_string(token->type), token->string);
		token = token->next;
	}
}
*/
char	*skip_spaces(char *string)
{
	while (*string && ft_strchr(" \f\v\n\t\r", *string))
		string++;
	return (string);
}

void	handle_quotes_expand(t_token *token, t_env *env)
{
	if (token->type == DOUBLE && ft_strchr(token->string, '$') != NULL)
		token->type = EXPANDABLE;
	if (token->type == DOUBLE || token->type == SINGLE)
		token->type = WORD;
	if (token->type == EXPANDABLE)
	{
		token->string = expand(token->string, env);
		token->type = WORD;
	}
}

/* recombine args and remove space tokens */
int	clean_spaces(t_token *token)
{
	while (token)
	{
		if (token->type == WORD)
		{
			while (token->next && token->next->type == WORD)
			{
				token->string = join(token->string, token->next->string);
				if (token->string == NULL)
					return (0);
				remove_next_token(token);
			}
		}
		while (token->next && token->next->type == SPACE_TOKEN)
			remove_next_token(token);
		token = token->next;
	}
	return (1);
}

t_token	*tokenize_string(char *line, t_env *env)
{
	t_token	*start;
	t_token	*new;

	start = NULL;
	line = skip_spaces(line);
	while (*line)
	{
		new = get_token(line);
		if (!new)
			return (tokenizer_norm_free(new, start));
		line += ft_strlen(new->string);
		if (new->type == SINGLE || new->type == DOUBLE)
			line += 2;
		handle_quotes_expand(new, env);
		if (new->string == NULL)
			return (tokenizer_norm_free(new, start));
		add_token_last(&start, new);
	}
	if (clean_spaces(start) == 0)
	{
		printf("clean spaces\n");
		return (NULL);
	}
	return (start);
}
/*
int	main(int argc, char **argv)
{
	t_token	*tokens;
	char	**testarr = ft_split("HOME=/user/home KEY=VALUE", ' ');
	t_env	*envtest = malloc(sizeof(t_env));
	envtest->arr = testarr;

	tokens = tokenize_string(ft_strdup(argv[1]), envtest);
	printf("\n-------------\n");
	printf("List created:\n");
	print_token(tokens);
	free_token_list(tokens);
	free_array(envtest->arr);
	free(envtest);
	return (0);
}*/
