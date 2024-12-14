/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:30:06 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/14 19:09:55 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "minishell.h"
# include <stdbool.h>

typedef struct s_minishell	t_minishell;

char	*heredoc(char *key, t_minishell *m, bool expand, int *error);
#endif