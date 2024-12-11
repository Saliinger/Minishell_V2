#include "../../include/exec.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (!dst)
		return ((char *)src);
	if (!src)
		return (dst);
	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*build_full_path(char *dir, char *cmd)
{
	char	*full_path;
	int		total_len;

	total_len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(sizeof(char) * total_len);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

static char	*get_value(char **splited_path, char *full_path, t_command *command)
{
	int	i;

	i = 0;
	while (splited_path[i])
	{
		full_path = build_full_path(splited_path[i],
				command->clean_arg[0]);
		if (!full_path)
		{
			free_split(splited_path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_split(splited_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(splited_path);
	return (NULL);
}

char	*get_path_abs(t_minishell *data, t_command *command)
{
	char	**splited_path;
	char	*full_path;
    char    *tmp;

	full_path = NULL;
	tmp = data->env[get_env_var(data, "PATH", 4)];
	splited_path = ft_split(tmp, ':');
	if (!splited_path)
		return (NULL);
	return (get_value(splited_path, full_path, command));
}


int    ft_exec_extern(t_minishell *minishell, t_command *command)
{
    char *path;

    path = get_path_abs(minishell, command);
    if (!path)
    {
        perror("Paths doesn't exist\n");
        return (1);
    }
    if (execve(path, command->clean_arg, minishell->env) == -1)
    {
        perror("Execution failed\n");
        return (1);
    }
    return (0);
}