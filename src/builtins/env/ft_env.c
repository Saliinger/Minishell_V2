/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:29:52 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 18:10:17 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// display env variable

#include "../../../include/minishell.h"

void	ft_env(t_minishell *minishell)
{
	int	i;

	if (!minishell->env)
		exit(1);
	i = 0;
	while (minishell->env[i])
	{
		printf("%s\n", minishell->env[i]);
		i++;
	}
	exit(0);
}
