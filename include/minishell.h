/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:22:12 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:10:01 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "enum.h"
# include "heredoc.h"
# include "imports.h"
# include "parsing.h"
# include "signals.h"
# include "structure.h"
# include "utils.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

// FREE
void			free_minishell(t_minishell *minishell);
void			free_command(t_command *command);

void			ft_free(void **address);
void			ft_free_nullterm_tab(char ***ptab);
void			free_t_minishell(t_minishell **m);

int				ft_minishell(t_minishell *minishell);

// UTILS
char			*display_prompt(char *prompt, t_minishell *minishell);
void			sighandler(int sig);
char			**get_env(char **env);
bool			checker_command(char *in, char *command);
int				nbr_of_line(char **env);

// Split Element
size_t			ft_countword(const char *s, char c);
int				ft_split_free(char **dest);
void			ft_split_write_word(char *dest, const char *src, int start,
					int end);
char			**split_element(char *s, char c);

// ENV_UTILITY
int				get_env_var(t_minishell *minishell, char *var, int len);

// Debug
void			ft_print(char **s, int i);
void			ft_print_redir(t_redir *list);
void			print_command(t_command *command, char *name);

// export list
int				add_node_export(t_export_list **list, char *name, char *value);
t_export_list	**init_export_list(char **env);
void			print_export_list(t_export_list **list);
void			merge_sort(t_export_list **head_ref);
char			*get_name_env(char *var);
char			*get_value_env(char *var);
int				modify_value(t_export_list **lst, char *name, char *value);
t_export_list	*find_export_node(char *name, t_export_list **lst);
int				delete_export_node(t_export_list **lst, char *name);

bool			check_access(char *path);

#endif

// get current dir si il n'y a pas d'env au debut
// bien up pwd path
//
