/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:29:52 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 18:30:51 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// display env variable

#include "../../../include/minishell.h"

int	ft_env(t_minishell *minishell)
{
	int	i;

	if (!minishell->env)
		return (1);
	i = 0;
	while (minishell->env[i])
	{
		printf("%s\n", minishell->env[i]);
		i++;
	}
	nuclear_exit(0);
}
