/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:16:09 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/14 19:09:42 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# ifndef VERBOSE
#  define VERBOSE 0
# endif

enum	e_errors
{
	ERR = 1,
	EXIT_EOF = 2,
	ERR_PRIM = -1
};

int		ft_error(char *error_msg, int errnum);
int		printerr(const char *format, ...);

#endif