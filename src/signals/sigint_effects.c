/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:16:49 by ekrebs            #+#    #+#             */
/*   Updated: 2024/11/28 01:05:27 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"
/**
 * brief : Ctrl + C effect when in mode heredoc
 * will close the STDIN, stopping the readline
 * (STDIN should be have been saved in main program to reopen in main program after.)
 */
void	sigeffect_heredoc_sigint()
{
	g_sig = 0; //SIG_EXIT;
	write(STDOUT_FILENO, "\n", 1);
	rl_done = 1;
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	close(STDIN_FILENO);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include <string.h>
/**
 * brief : Ctrl + C effect when in mode minishell
 * 
 */
void	sigeffect_minishell_sigint()
{
	g_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
}
