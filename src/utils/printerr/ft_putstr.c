/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:46:49 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/28 14:57:43 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	ft_pr_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_pr_putchar_fd_printf(str[i], STDERR_FILENO);
		++i;
	}
	return (i);
}
