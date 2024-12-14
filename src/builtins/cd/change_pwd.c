/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:42:23 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:07:25 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// delte pwd get the new one
// old pwd = pwd before deletw

static int	undpate_pwd(t_minishell *minishell, char *path, int oldpwd_line,
		int pwd_line)
{
	int				error;
	t_export_list	*temp;
	char			*temp2;

	error = 0;
	temp = find_export_node("PWD", minishell->export_list);
	if (!temp)
	{
		temp2 = ft_strjoin_safe("PWD=", path, ALLOC_MINISHELL);
		create_var(minishell, temp2);
		add_node_export(minishell->export_list, "PWD", path);
		temp = find_export_node("PWD", minishell->export_list);
	}
	error += modify_value(minishell->export_list, "OLDPWD", temp->value);
	minishell->old_pwd = ft_strjoin_safe("OLDPWD=", temp->value,
			ALLOC_MINISHELL);
	minishell->env[oldpwd_line] = safe_strdup(minishell->old_pwd,
			ALLOC_MINISHELL);
	error += modify_value(minishell->export_list, "PWD", path);
	minishell->pwd = safe_strdup(path, ALLOC_MINISHELL);
	minishell->env[pwd_line] = ft_strjoin_safe("PWD=", minishell->pwd,
			ALLOC_MINISHELL);
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
