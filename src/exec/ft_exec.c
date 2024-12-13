/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 01:59:00 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/13 21:45:14 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// launch exec for builtins and extern command

int	ft_exec(t_minishell *minishell, t_command *command)
{
	int	exit;

	exit = 0;
	// printf("builtin: %d\nbin id: %d\n", command->builtin, command->id);
	if (command->builtin)
		exit = ft_exec_builtins(minishell, command);
	else
		exit = ft_exec_extern(minishell, command);
	safe_malloc(0, DESTROY_COMMAND);
	return (exit);
}
