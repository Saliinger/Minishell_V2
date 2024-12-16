/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:00 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 19:07:08 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_echo(t_command *command)
{
	int		i;
	char	**cmd;
	int		error;

	cmd = command->clean_arg + 1;
	i = check_flag(cmd);
	error = 0;
	if (i > 0)
		error += echo_print(cmd, false, i);
	else
		error += echo_print(cmd, true, i);
	if (error > 0)
		return(nuclear_exit(EXIT_FAILURE));
	return (nuclear_exit(EXIT_SUCCESS));
}
