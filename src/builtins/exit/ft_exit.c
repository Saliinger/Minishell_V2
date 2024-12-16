/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:09 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 18:31:00 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	check_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_exit_extend(int exit_code)
{
	safe_malloc(0, NUKE);
	nuclear_exit(exit_code);
}

void	ft_exit(t_minishell *minishell, t_command *command, bool fail)
{
	(void)minishell;
	(void)command;
	if (nbr_of_line(command->clean_arg) >= 3)
	{
		printerr("bash: exit: too many arguments\n");
		ft_exit_extend(1);
	}
	if (nbr_of_line(command->clean_arg) == 2
		&& check_arg(command->clean_arg[1]) == true)
	{
		printerr(" numeric argument required\n");
		ft_exit_extend(2);
	}
	else if (command->clean_arg[1] && fail == false)
		ft_exit_extend(atoi(command->clean_arg[1]));
	else if (fail == true)
		ft_exit_extend(EXIT_FAILURE);
	else
		ft_exit_extend(minishell->exit_status[0]);
}

// add error 255 if word as arg if 3 arg return 1