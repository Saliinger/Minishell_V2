/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:31:01 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:07:47 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	remove_path(char *dest)
{
	int	len;

	len = ft_strlen(dest);
	if (len == 0)
		return ;
	while (len > 0 && dest[len] != '/')
	{
		dest[len] = 0;
		len--;
	}
	dest[len] = 0;
}

void	add_path(char *dest, char *to_add)
{
	int	j;
	int	i;
	int	len;

	len = ft_strlen(dest);
	if (dest[len] != '/')
		dest[len] = '/';
	j = len + 1;
	i = 0;
	while (to_add[i] && to_add[i + 1] != '/')
	{
		dest[j] = to_add[i];
		j++;
		i++;
	}
	dest[j] = '\0';
}
