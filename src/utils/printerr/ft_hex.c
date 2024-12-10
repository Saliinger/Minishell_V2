/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0006/11/20 14:18:23 by noukan            #+#    #+#             */
/*   Updated: 2024/11/28 14:57:13 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

void	ft_pr_putnb(unsigned int nb, const char c)
{
	if (nb >= 16)
	{
		ft_pr_putnb(nb / 16, c);
		ft_pr_putnb(nb % 16, c);
	}
	else
	{
		if (nb <= 9)
			ft_pr_printchar(nb + '0');
		else
		{
			if (c == 'x')
				ft_pr_printchar(nb - 10 + 'a');
			if (c == 'X')
				ft_pr_printchar(nb - 10 + 'A');
		}
	}
}

int	ft_pr_hex(unsigned int nb, const char c)
{
	if (nb == 0)
		return (ft_pr_printchar('0'));
	else
		ft_pr_putnb(nb, c);
	return (ft_pr_hexcount(nb));
}
