/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:06:59 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 18:20:16 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "imports.h"
# include "structure.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/stat.h>

// CD
void	ft_cd(t_command_exec *command, t_minishell *minishell);
char	*get_path(char *in, t_minishell *minishell);
char	*get_home(t_minishell *minishell);
char	*path_constructor(t_minishell *minishell, char *in);
char	*get_current_path(t_minishell *minishell);
int		change_pwd(t_minishell *minishell, char *in);
void	remove_path(char *dest);
void	add_path(char *dest, char *to_add);

// ECHO
void	ft_echo(t_command_exec *command);
int		echo_print(char **arg, bool eof, int i);
int		check_flag(char **arg);

// ENV
void	ft_env(t_minishell *minishell);

// EXIT
void	ft_exit(t_minishell *minishell, t_command_exec *command, bool fail);

// EXPAND
void	ft_expand(t_command_exec *command, t_minishell *minishell);

// PWD
void	ft_pwd(t_minishell *minishell);

// UNSET
void	ft_unset(t_command_exec *command, t_minishell *minishell);

// EXPORT
void	ft_export(t_command_exec *command, t_minishell *minishell);
int		create_var(t_minishell *minishell, char *var);
int		delete_var(t_minishell *minishell, int line);

#endif
