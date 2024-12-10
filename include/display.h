/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:53:58 by ekrebs            #+#    #+#             */
/*   Updated: 2024/11/28 23:44:04 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "imports.h"

typedef struct s_command_exec t_command_exec;
typedef struct s_redir t_redir;

void	print_cmd_node(t_command_exec *c, char *display_name);
void	print_cmd_nodes(t_command_exec *c, char *display_name);
void	print_args(t_command_exec *c);
void	print_display_name(char *display_name);
void	print_redir(t_redir *redir);
void	print_redirs(t_redir *redir);
void	print_std_fds(int *fds, char *display_name);
void	print_body(t_command_exec *c);
void	print_fds(int *fds, char *name, char *display_name);
void	print_pipes(int **pipes, int pipe_count, char *name);
#endif
