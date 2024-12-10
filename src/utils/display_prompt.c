/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:34:56 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 17:32:00 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_prompt_pwd(char *pwd, char *user)
{
	char	*home_prefix;
	size_t	prefix_len;
	char	*simplified_pwd;

	if (!pwd)
		return (NULL);
	if (!user)
		return (ft_strdup(pwd));
	prefix_len = ft_strlen("/home/") + ft_strlen(user);
	home_prefix = ft_strjoin("/home/", user);
	if (ft_strncmp(home_prefix, pwd, prefix_len) == 0)
	{
		simplified_pwd = ft_strjoin("~", &pwd[prefix_len]);
		return (free(home_prefix), simplified_pwd);
	}
	return (free(home_prefix), ft_strdup(pwd));
}

char	*display_prompt(char *prompt, t_minishell *minishell)
{
	char	*pwd;
	char	*usr;
	char	*name;
	char	*res;

	if (prompt)
		free(prompt);
	usr = getenv("LOGNAME");
	name = getenv("NAME");
	pwd = get_prompt_pwd(minishell->pwd, usr);
	if (usr && name)
	{
		res = ft_strjoin(AINSI_BGREEN, usr);
		res = ft_strjoin_frees1(res, "@");
		res = ft_strjoin_frees1(res, name);
		res = ft_strjoin_frees1(res, AINSI_RESET);
		res = ft_strjoin_frees1(res, ":");
		res = ft_strjoin_frees1(res, AINSI_BLUE);
		res = ft_strjoin_frees1(res, pwd);
	}
	else
		res = ft_strjoin(AINSI_BLUE, pwd);
	res = ft_strjoin_frees1(res, AINSI_RESET);
	res = ft_strjoin_frees1(res, "$ ");
	return (free(pwd), res);
}
