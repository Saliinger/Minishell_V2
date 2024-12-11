/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:00 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 18:20:35 by anoukan          ###   ########.fr       */
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
	if (i > 0)
		error = echo_print(cmd, false, i);
	else
		error = echo_print(cmd, true, i);
	exit (error);
}