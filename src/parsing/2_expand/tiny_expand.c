#include "../../../include/minishell.h"

char *tiny_expand(char *s, t_minishell *minishell)
{
    char *res;
    char *name;
    t_export_list *var;

    if (*s == '$')
    {
        name = get_name_env(s);
        var = find_export_node(name, minishell->exportList);
        if (!var || !var->value)
        {
            res = ft_strdup(s + ft_strlen(name));
            free(s);
            free(name);
            return (res);
        }
        res = ft_strdup(var->value);
        res = ft_strjoin_frees1(res, s + ft_strlen(name));
    }
    else
        return (s);
    free(name);
    free(s);
    return (res);
}