/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:19:49 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/14 19:18:01 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_signals_to_heredoc(void)
{
	int					err;
	struct sigaction	sa;

	err = 0;
	sa.sa_flags = 0;
	err += sigemptyset(&sa.sa_mask);
	err += sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_handler = heredoc_signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	return (EXIT_SUCCESS);
}

int	set_signals_to_minishell(void)
{
	int					err;
	struct sigaction	sa;

	err = 0;
	sa.sa_flags = 0;
	err += sigemptyset(&sa.sa_mask);
	err += sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_handler = minishell_signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	return (EXIT_SUCCESS);
}

int	set_signals_to_default(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (perror("sigemptyset"), ERR_PRIM);
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	return (EXIT_SUCCESS);
}

int	set_signals_to_ignore(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (perror("sigemptyset"), ERR_PRIM);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	return (EXIT_SUCCESS);
}
