/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:19:41 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/28 15:00:28 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

void	ft_pr_putchar_fd_printf(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_pr_putnbr_fd_printf(int nb, int fd)
{
	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nb >= 0 && nb <= 9)
		ft_pr_putchar_fd_printf(nb + '0', fd);
	else if (nb < 0)
	{
		ft_pr_putchar_fd_printf('-', fd);
		ft_pr_putnbr_fd_printf(nb * -1, fd);
	}
	else
	{
		ft_pr_putnbr_fd_printf(nb / 10, fd);
		ft_pr_putchar_fd_printf(nb % 10 + '0', fd);
	}
}
