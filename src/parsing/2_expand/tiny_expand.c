#include "../../../include/minishell.h"

char *get_name(char *s, t_minishell *minishell)
{
    int i = 0;
    int start = 0;
    int end = 0;
    char *name;

	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
    start = i;
    while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
    end = i - start + 1;
    name = (char *) safe_malloc(sizeof(char) * end + 1, minishell);
    ft_strlcpy(name,s + start, end);
    return (name);
}

char *tiny_expand(char *s, t_minishell *minishell)
{
    char *res;
    char *name;
    t_export_list *var;

    if (*s == '$')
    {
        name = get_name(s, minishell);
        var = find_export_node(name + 1, minishell->exportList);
        if (!var || !var->value)
        {
            res = safe_strdup(s + ft_strlen(name), minishell);
            free(s);
            return (res);
        }
        res = safe_strdup(var->value, minishell);
        res = ft_strjoin_frees1(res, s + ft_strlen(name));
    }
    else
        return (s);
    free(s);
    return (res);
}