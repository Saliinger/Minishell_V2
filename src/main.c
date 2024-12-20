/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:32:10 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 05:45:05 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_minishell	*init(char **env, char *pwd, int *adr_int)
{
	t_minishell	*minishell;

	minishell = (t_minishell *)safe_malloc(sizeof(t_minishell),
			ALLOC_MINISHELL);
	if (!minishell)
		return (NULL);
	if (!env)
		minishell->env = init_no_env();
	else
		minishell->env = get_env(env);
	minishell->pwd = safe_strdup(pwd, ALLOC_MINISHELL);
	minishell->old_pwd = safe_strdup(pwd, ALLOC_MINISHELL);
	minishell->res_last_command = 0;
	minishell->std_fds[0] = -1;
	minishell->std_fds[1] = -1;
	minishell->paths = NULL;
	minishell->exit_status = adr_int;
	minishell->hidden_env = NULL;
	if (!env)
		minishell->export_list = init_no_env_export();
	else
		minishell->export_list = init_export_list(minishell->env);
	merge_sort(minishell->export_list);
	return (minishell);
}

volatile sig_atomic_t	g_sig = NO_SIG;

int	main(int ac, char **av, char **env)
{
	int			exit_status;
	t_minishell	*minishell;
	char		buffer[4096 + 1];

	set_signals_to_minishell();
	(void)av;
	if (ac > 1 || isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
		return (printerr("err: case not asked by subject.\n"), 1);
	exit_status = 0;
	minishell = init(env, getcwd(buffer, 4096), &exit_status);
	if (!minishell)
		return (1);
	ft_minishell(minishell);
	clear_history();
	safe_malloc(0, NUKE);
	return (exit_status);
}
