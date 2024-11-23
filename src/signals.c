/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:15:45 by mshabano          #+#    #+#             */
/*   Updated: 2024/11/23 13:13:42 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fork_sig_handler(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	if (signum == SIGINT)
		ft_putchar_fd('\n', 1);
}

static void	heredoc_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 2;
		close(0);
	}
}

static void	main_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 1;
	}
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_main_signals(void)
{
	signal(SIGINT, main_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
