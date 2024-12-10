/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:32:10 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 22:59:01 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_minishell	*init(char **env, char *pwd, int *adr_int)
{
	t_minishell	*minishell;

	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
		return (NULL);
	minishell->env = get_env(env);
	minishell->pwd = ft_strdup(pwd);
	minishell->old_pwd = ft_strdup(pwd);
	minishell->res_last_command = 0;
	// minishell->hd = (char **)malloc(sizeof(char *));
	// minishell->hd[0] = NULL;
	minishell->std_fds[0] = -1;
	minishell->std_fds[1] = -1;
	minishell->paths = NULL;
	minishell->exit_status = adr_int;
	minishell->hidden_env = NULL;
	minishell->exportList = init_export_list(minishell->env);
	merge_sort(minishell->exportList);
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
	if (ac > 1)
		return (printerr("err: case not asked by subject\n."), 1);
	exit_status = 0;
	minishell = init(env, getcwd(buffer, 4096), &exit_status);
	if (!minishell)
		return (1);
	if (save_std_fds(minishell->std_fds) == -1)
		return (ERR_PRIM);
	ft_minishell(minishell);
	clear_history();
	free_t_minishell(&minishell);
	return (exit_status);
}
