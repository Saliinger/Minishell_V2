/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:22:20 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/14 19:10:11 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# define NO_SIG 0

extern volatile sig_atomic_t	g_sig;

int								set_signals_to_minishell(void);
int								set_signals_to_default(void);
int								set_signals_to_ignore(void);
int								set_signals_to_heredoc(void);

void							minishell_signal_handler(int signal);
void							heredoc_signal_handler(int signal);

#endif