/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:56:29 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/28 14:57:35 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

void	ft_pr_putnbr_u(unsigned long nbr)
{
	if (nbr <= 9)
		ft_pr_printchar(nbr + '0');
	else
	{
		ft_pr_putnbr_u(nbr / 10);
		ft_pr_printchar(nbr % 10 + '0');
	}
}
