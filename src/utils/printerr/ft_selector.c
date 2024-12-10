/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:01:50 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/28 15:00:28 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

void	ft_pr_selector(const char *format, va_list args, int *count)
{
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			if (*format == 'd' || *format == 'i')
				*count += ft_pr_decimal(va_arg(args, int));
			else if (*format == 's')
				*count += ft_pr_string(va_arg(args, char *));
			else if (*format == 'c')
				*count += ft_pr_printchar(va_arg(args, int));
			else if (*format == 'u')
				*count += ft_pr_uint(va_arg(args, int));
			else if (*format == 'X' || *format == 'x')
				*count += ft_pr_hex(va_arg(args, unsigned int), *format);
			else if (*format == 'p')
				*count += ft_pr_pointertohex(va_arg(args, unsigned long long));
			else if (*format == '%')
				*count += ft_pr_printchar('%');
		}
		else
			*count += ft_pr_printchar(*format);
		++format;
	}
}
