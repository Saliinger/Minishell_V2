/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:42:23 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 12:51:14 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// delte pwd get the new one
// old pwd = pwd before deletw

static int	undpate_pwd(t_minishell *minishell, char *path, int oldpwd_line,
		int pwd_line)
{
	int	error;

	error = 0;
	free(minishell->old_pwd);
	minishell->old_pwd = ft_strdup(minishell->pwd);
	if (!minishell->old_pwd)
		return (1);
	free(minishell->env[oldpwd_line]);
	minishell->env[oldpwd_line] = ft_strjoin("OLDPWD=", minishell->old_pwd);
	free(minishell->pwd);
	minishell->pwd = ft_strdup(path);
	if (!minishell->pwd)
		return (1);
	free(minishell->env[pwd_line]);
	minishell->env[pwd_line] = ft_strjoin("PWD=", path);
	error += modify_value(minishell->exportList, "PWD", minishell->pwd);
	error += modify_value(minishell->exportList, "OLDPWD", minishell->old_pwd);
	return (error);
}

int	change_pwd(t_minishell *minishell, char *in)
{
	int		pwd_line;
	int		oldpwd_line;
	char	cwd[PATH_MAX];
	char	*path;

	pwd_line = get_env_var(minishell, "PWD=", 4);
	oldpwd_line = get_env_var(minishell, "OLDPWD=", 7);
	if (pwd_line == -1 || oldpwd_line == -1)
		return (1);
	if (!in)
	{
		getcwd(cwd, PATH_MAX);
		path = cwd;
	}
	else
		path = in;
	return (undpate_pwd(minishell, path, oldpwd_line, pwd_line));
}
