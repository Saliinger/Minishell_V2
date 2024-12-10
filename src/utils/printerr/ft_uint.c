/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:58:15 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/28 15:00:28 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	ft_pr_uint(int value)
{
	unsigned int	unsigned_value;

	if (value < 0)
		unsigned_value = (unsigned int)value + 4294967296;
	else
		unsigned_value = (unsigned int)value;
	ft_pr_putnbr_u(unsigned_value);
	return (ft_pr_countdigit_u(unsigned_value));
}
