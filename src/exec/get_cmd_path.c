/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:58:26 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/15 19:26:34 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "errno.h"


/**
 * 
 * brief : adds the cmd_name after the env_path;
 * 
 */
char	*build_full_path(char *env_path, char *cmd_name)
{
	char	*full_path;
	int		total_len;

	total_len = ft_strlen(env_path) + ft_strlen(cmd_name) + 2;
	full_path = (char *)safe_malloc(sizeof(char) * total_len, ALLOC_COMMAND);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, env_path);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd_name);
	return (full_path);
}

/**
 * 
 * brief :gets the executable cmd_path,
 * checks by adding 
 * 
 * 
 */
static char	*get_command(char **env_paths, char* cmd_name, int *err)
{
	char *full_path;
	int	i;

	full_path = NULL;
	i = 0;
	while (env_paths[i])
	{
		full_path = build_full_path(env_paths[i], cmd_name);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	printerr("%s: command not found\n", cmd_name);
	return (*err = 127, NULL);
}

/**
 * brief : returns tab of paths found in the env, 
 * if fails, returns NULL
 * 
 *  */
static char	**get_env_paths(t_minishell *m)
{
	char	*tmp;
	char	**result;

	tmp = m->env[get_env_var(m, "PATH", 4)];
	result = ft_split_safe(tmp, ':', ALLOC_COMMAND);
	return (result);
}

/**
 * brief : returns appropriate for or dir error if name is not executable.
 * 
 */
static char	*get_file_or_dir(char *name, int *err)
{
	struct stat	f;

	if (lstat(name, &f) == -1)
	{
		if (errno == ENOTDIR)
			*err = 126;
		else
			*err = 127;
		return (printerr("minishell: "), perror(name), NULL);
	}
	if (S_ISDIR(f.st_mode))
		return (printerr("minishell: %s: is a directory\n", name), \
														*err = 126, NULL);
	return (name);
}

/**
 * brief : returns the path of the cmd to exec. checks for dir 
 * 							or file if starts with ./ or contains /, 
 * will display error correctly for valid cmd path not found.
 * if fails, returns NULL
 * 
 *  */
char	*get_cmd_path(char *cmd_name, t_minishell *m, int *err)
{
	char	**env_paths;
	char	*cmd_path;

	env_paths = get_env_paths(m);
	if (ft_strchr(cmd_name, '/'))
	{
		cmd_path = get_file_or_dir(cmd_name, err); //
	}
	else if (cmd_name[0] == '.')
	{
		return (printerr("%s: command not found\n", cmd_name), \
														*err = 127, NULL); //
	}
	else
		cmd_path = get_command(env_paths, cmd_name, err); //
	return (cmd_path);
}
