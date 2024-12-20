/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:31:01 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 05:47:08 by ekrebs           ###   ########.fr       */
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
	size_t	len;

	if (!*to_add)
		return ;
	len = ft_strlen(dest);
	if (len > 0 && dest[len - 1] != '/')
		ft_strlcat(dest, "/", PATH_MAX);
	ft_strlcat(dest, to_add, PATH_MAX);
}
