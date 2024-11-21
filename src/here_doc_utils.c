/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:07:13 by mshabano          #+#    #+#             */
/*   Updated: 2024/11/21 17:07:15 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unexpected_eof(char *i, char *eof)
{
	if (!i)
		i = "0";
	ft_putstr_fd("-minishell: warning: here-document at line ", 2);
	ft_putstr_fd(i, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
	free(i);
}

int	interrupt_here_doc(char *eof, char *s, int *r_value, int i)
{
	if (g_signal == 2)
	{
		*r_value = 130;
        unlink(".here_doc");
		return (1);
	}
	if (!s)
	{
		unexpected_eof(ft_itoa(i), eof);
		return (1);
	}
	if (!ft_strcmp(s, eof))
	{
		free(s);
		return (1);
	}
	return (0);
}
