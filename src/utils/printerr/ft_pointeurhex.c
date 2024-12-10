/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointeurhex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:14:14 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/28 14:59:30 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

void	ft_pr_printptr(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ft_pr_printptr(ptr / 16);
		ft_pr_printptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_pr_printchar(ptr + '0');
		else
			ft_pr_printchar(ptr - 10 + 'a');
	}
}

int	ft_pr_pointertohex(unsigned long long ptr)
{
	int	i;

	i = 0;
	i += ft_pr_putstr("0x");
	if (ptr == 0)
		i += ft_pr_printchar('0');
	else
	{
		ft_pr_printptr(ptr);
		i += ft_pr_ptrlen(ptr);
	}
	return (i);
}
