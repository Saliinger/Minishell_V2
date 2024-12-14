/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:13:52 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/14 19:09:45 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;

# define IN 0
# define OUT 1

# define RE 0
# define WE 1

int							ft_exec(t_minishell *minishell, t_command *command);
int							ft_exec_builtins(t_minishell *minishell,
								t_command *command);
int							ft_exec_extern(t_minishell *minishell,
								t_command *command);
void						process_input_line(char *line, t_minishell *m);

// Utils
void						exec_error(char *error, t_minishell *minishell,
								t_command *command);
int							count_cmd(t_command *command);

#endif