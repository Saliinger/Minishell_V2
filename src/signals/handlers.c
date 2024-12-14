/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:19:51 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/14 19:10:50 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *
 * brief : writes '\n' then clears prompt and closes the STDIN
 *  for readline to get EOF and return NULL
 *
 */
void	heredoc_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		close(STDIN_FILENO);
	}
}

/**
 *
 * brief : writes '\n' then clears and redisplays the promt *
 */
void	minishell_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}
