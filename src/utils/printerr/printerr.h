/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printerr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0003/11/20 13:05:09 by noukan            #+#    #+#             */
/*   Updated: 2024/11/28 15:00:28 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTERR_H
# define PRINTERR_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

int		printerr(const char *format, ...);

// Selector
void	ft_pr_selector(const char *format, va_list args, int *count);

// Char/String part
int		ft_pr_printchar(char c);
int		ft_pr_putstr(char *str);
int		ft_pr_string(char *str);

// Decimal part
int		ft_pr_countdigit(long nbr);
int		ft_pr_decimal(int n);

// Unsigned Int
int		ft_pr_uint(int value);
int		ft_pr_countdigit_u(unsigned long nbr);
void	ft_pr_putnbr_u(unsigned long nbr);

// Hex part
int		ft_pr_hex(unsigned int nbr, const char c);
int		ft_pr_hexcount(unsigned int n);
int		ft_pr_pointertohex(unsigned long long ptr);
int		ft_pr_ptrlen(uintptr_t ptr);

// Utils
void	ft_pr_putnbr_fd_printf(int nb, int fd);
void	ft_pr_putchar_fd_printf(char c, int fd);


#endif
