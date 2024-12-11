/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:26 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 18:18:12 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_unset(t_command *command, t_minishell *minishell)
{
	int	i;
	int	line;


	if (nbr_of_line(command->clean_arg) > 1)
	{
        i = 1;
	    line = 0;
		while (command->clean_arg[i])
		{
			line = get_env_var(minishell, command->clean_arg[i],
					ft_strlen(command->clean_arg[i]));
			if (line != -1)
			{
				delete_var(minishell, line);
				delete_export_node(minishell->exportList, command->clean_arg[i]);
			}
			i++;
		}
	}
    return (0);
}
