/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:21:21 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 16:08:02 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// chekc if there's pipe and give their position in the char *in

size_t	check_pipe(char *in)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < ft_strlen(in) && in[i])
	{
		if (in[i] == '|')
			return (i);
		if (in[i] == '\'' || in[i] == '\"')
		{
			flag = in_quote(flag, in[i]);
			i++;
			while (in[i] && flag != 0)
			{
				flag = in_quote(flag, in[i]);
				i++;
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}
