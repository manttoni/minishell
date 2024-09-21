/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:48:14 by amaula            #+#    #+#             */
/*   Updated: 2024/05/04 18:08:46 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_words(const char *s, char c)
{
	unsigned int	words_amt;

	words_amt = 0;
	while (s && *s)
	{
		while (*s == c)
			s++;
		if (*s)
			words_amt++;
		s = ft_strchr(s, c);
	}
	return (words_amt);
}

static char	**free_all(char **s, unsigned int i)
{
	while (i > 0)
		free(s[--i]);
	free(s);
	return (NULL);
}

static char	*get_word(const char *start, char *end)
{
	if (end == NULL)
		return (ft_strdup(start));
	return (ft_substr(start, 0, end - start));
}

char	**ft_split(const char *s, char c)
{
	char			**splitted_string;
	char			*ptr;
	unsigned int	i;

	if (!s)
		return (NULL);
	splitted_string = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (splitted_string == NULL)
		return (NULL);
	i = 0;
	while (s && *s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		ptr = ft_strchr(s, c);
		splitted_string[i] = get_word(s, ptr);
		if (splitted_string[i] == NULL)
			return (free_all(splitted_string, i));
		i++;
		s = ptr;
	}
	splitted_string[i] = NULL;
	return (splitted_string);
}
