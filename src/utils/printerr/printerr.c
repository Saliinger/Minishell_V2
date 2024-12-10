/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printerr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0003/11/20 13:05:51 by noukan            #+#    #+#             */
/*   Updated: 2024/11/28 14:58:06 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	printerr(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	ft_pr_selector(format, args, &count);
	va_end(args);
	return (count);
}
