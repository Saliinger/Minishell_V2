/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:19:49 by ekrebs            #+#    #+#             */
/*   Updated: 2024/11/26 23:15:53 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"
int	set_signals_to_heredoc(void)
{
	int					err;
	struct sigaction	sa;

	// Initialiser la structure sigaction
	err = 0;
	sa.sa_flags = 0;                		// Pas de flags supplémentaires
	err += sigemptyset(&sa.sa_mask);	
	err += sigaddset(&sa.sa_mask, SIGINT);	// bloquer sigint pendant handler
	sa.sa_handler = heredoc_signal_handler;	// Définir la fonction de gestion
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
    return (EXIT_SUCCESS);
}

int	set_signals_to_minishell(void) //cas particulier minishell imbriqué // bash imbriqué -> sigignore
{
	int					err;
	struct sigaction	sa;

	// Initialiser la structure sigaction
	err = 0;
	sa.sa_flags = 0;                			// Pas de flags supplémentaires
	err += sigemptyset(&sa.sa_mask);			// bloquer sigint pendant handler
	err += sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_handler = minishell_signal_handler;	// Définir la fonction de gestion
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	 	return (perror("sigaction"), ERR_PRIM);
    return (EXIT_SUCCESS);
}

int	set_signals_to_default(void)
{
	struct sigaction sa;

	// Initialiser la structure sigaction
	sa.sa_flags = 0;                	// Pas de flags supplémentaires
	if (sigemptyset(&sa.sa_mask) == -1)			// Ne bloquer aucun autre signal pendant le traitement
		return (perror("sigemptyset"), ERR_PRIM);
	sa.sa_handler = SIG_DFL;	// Définir la fonction de gestion
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
    return (EXIT_SUCCESS);
}

int	set_signals_to_ignore(void)
{
	struct sigaction sa;

	// Initialiser la structure sigaction
	sa.sa_flags = 0;                	// Pas de flags supplémentaires
	if (sigemptyset(&sa.sa_mask) == -1)			// Ne bloquer aucun autre signal pendant le traitement
		return (perror("sigemptyset"), ERR_PRIM);
	sa.sa_handler = SIG_IGN;	// Définir la fonction de gestion
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (perror("sigaction"), ERR_PRIM);
    return (EXIT_SUCCESS);
}


