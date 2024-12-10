/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:30:06 by ekrebs            #+#    #+#             */
/*   Updated: 2024/11/28 23:44:49 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HEREDOC_H
#define HEREDOC_H
#include "minishell.h"

char	*heredoc(char *key, t_minishell *m, bool expand, int *error);
#endif