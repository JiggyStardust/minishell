/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:24:58 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:32:50 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_heredoc(void *handler)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = handler;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_ignore(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = SIG_IGN;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_child(void *handler)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = handler;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = handler;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_reset(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = SIG_DFL;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_DFL;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_init(void *handler)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = handler;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}
