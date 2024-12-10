/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:07:28 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/29 22:37:51 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell t_minishell;
typedef struct s_command t_command;

char		**relexer(char **in);
char **expand_in(char **arg, t_minishell *minishell);
// PARSING
t_command	*command_init(char *in);
t_command	*parsing(char *str, t_minishell *minishell);
t_command	*trim(char *in, char *in_command, bool builtin, int id);
bool		input_checker(char *in);
t_redir		*extract_redir(char **in);
char		**clean_arg(char **arg);

char *add_char(char *s, char c);
char *clean_name(char *var);

char    **remove_quote(char **arg);

// Divider for parsing
int			check_pipe(char *in);

#endif
