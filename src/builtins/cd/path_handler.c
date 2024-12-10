/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:31:01 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 15:31:40 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"

void	remove_path(char *dest)
{
	int	len;

	len = ft_strlen(dest);
	if (len == 0)
		return ;
	while (len > 0 && dest[len - 1] != '/')
		len--;
	if (len == 0)
		dest[0] = '\0';
	else
		dest[len - 1] = '\0';
}

void	add_path(char *dest, char *to_add)
{
	int	j;
	int	i;
	int	len;

	len = ft_strlen(dest);
	dest[len] = '/';
	j = len + 1;
	i = 0;
	while (to_add[i])
	{
		dest[j] = to_add[i];
		j++;
		i++;
	}
	dest[j] = '\0';
}
