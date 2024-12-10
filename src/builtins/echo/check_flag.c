/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:28:37 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 22:59:57 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_flag(char **arg)
{
	int		n;
	size_t	i;
	size_t	j;

	n = 0;
	i = 0;
	while (arg[i])
	{
		j = 0;
		if (arg[i][j] == '-' && arg[i][j + 1] == 'n')
		{
			j++;
			while (arg[i][j] == 'n')
				j++;
			if (j == ft_strlen(arg[i]))
				n++;
			else
				return (n);
		}
		else
			break ;
		i++;
	}
	return (n);
}
