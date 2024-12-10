/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:48:42 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/10 11:55:56 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structure.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

typedef struct s_minishell		t_minishell;
typedef struct s_command_exec	t_command_exec;
typedef struct s_infos			t_infos;

//int								ft_strcmp(char *s1, char *s2);

void							ft_free(void **add);
void							ft_free_nullterm_tab(char ***ptab);
void							free_t_command_exec(t_command_exec **c);
void							free_t_command_exec_node(t_command_exec **c);
void							free_t_minishell(t_minishell **ms);
void							ft_free_t_redir(t_redir **r);
void							free_t_infos(t_infos *i);
void							ft_free_tab(char **tab);
int								in_quote(int status, char type);
char							**add_line(char **tab, char *to_add);
#endif
