/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:15:45 by mshabano          #+#    #+#             */
/*   Updated: 2024/12/05 17:05:55 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_sig_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("quit:(core dumped)\n", 1);
		g_signal = 5;
	}
	if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
}

static void	heredoc_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 2;
		if (close(0) == -1)
			print_error("unable to close(0)", 0);
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

void	*is_sig_err(void *a, void *b)
{
	if (a == SIG_ERR)
		return (a);
	if (b == SIG_ERR)
		return (b);
	return (0);
}

int	setup_signals(t_signal_type sig)
{
	void	*ret;

	ret = 0;
	if (sig == MAIN_SIG)
	{
		ret = is_sig_err(ret, signal(SIGINT, main_sig_handler));
		ret = is_sig_err(ret, signal(SIGQUIT, SIG_IGN));
	}
	else if (sig == FORK_SIG)
	{
		ret = is_sig_err(ret, signal(SIGINT, fork_sig_handler));
		ret = is_sig_err(ret, signal(SIGQUIT, fork_sig_handler));
	}
	else if (sig == HEREDOC_SIG)
	{
		ret = is_sig_err(ret, signal(SIGINT, heredoc_sig_handler));
		ret = is_sig_err(ret, signal(SIGQUIT, SIG_IGN));
	}
	if (ret == SIG_ERR)
	{
		print_error("unable to set signals", 0);
		return (1);
	}
	return (0);
}
