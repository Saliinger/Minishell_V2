/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:07:08 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/29 05:25:39 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

#define AINSI_BGREEN	"\033[1;32m"
#define AINSI_BLUE		"\033[1;34m"
#define AINSI_RESET		"\033[0m"

typedef enum e_redir
{
	R_IN_FILE= 1,
    R_IN_HEREDOC,
	R_IN_HEREDOC_Q,
    R_OUT_FILE_TRUNC,
	R_OUT_FILE_APPEND,
	R_INVALID,
}	t_enum_redir;

typedef enum e_cmd_type
{
	CMD_BUILTIN = 1,
	CMD_EXTERN,
} t_cmd_type;

#endif
 