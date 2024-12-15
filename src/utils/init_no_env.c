/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:14:21 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/15 21:14:26 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **init_no_env(void)
{
  char **env;
  char buffer[PATH_MAX + 1];

  getcwd(buffer, PATH_MAX);
  env = (char **)safe_malloc(sizeof(char *) * 4, ALLOC_MINISHELL);
  env[0] = ft_strjoin_safe("PWD=", buffer, ALLOC_MINISHELL);
  env[1] = safe_strdup("SHLVL=1", ALLOC_MINISHELL);
  env[2] = safe_strdup("_=/usr/bin/env", ALLOC_MINISHELL);
  env[3] = NULL;
  return (env);
}

// value on env
// PWD= the actual pwd
// SHLVL= current shlvl
// _=/usr/bin/env the path to env
// NULL

// export value
// OLDPWD
// PWD
// SHLVL